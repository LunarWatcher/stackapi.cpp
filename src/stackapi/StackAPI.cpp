#include "StackAPI.hpp"
#include "stackapi/errors/APIException.hpp"

#include <stdexcept>

namespace stackapi {

StackAPI::StackAPI(const APIConfig& conf, bool dryRun) : conf(conf), dryRun(dryRun) {
    if (conf.apiKey == "") {
        throw std::runtime_error("Misconfiguration: an API key is required.");
    }

    sess.sess.SetUserAgent(conf.userAgent);
}

nlohmann::json StackAPI::postRaw(const std::string& dest,
                    const std::map<std::string, std::string>& postBodyExtras,
                    const APIConfigOpt& opt) {
    if (dryRun) {
        return {};
    }
    bool faulted = false;
    do {
        if (opt.autoHandleBackoff.value_or(conf.autoHandleBackoff)) {
            checkBackoff();
        }

        cpr::Payload body = {
            {"key", conf.apiKey},
            {"site", opt.site.value_or(conf.site)}
        };

        if (opt.filter) {
            body.Add({"filter", *opt.filter});
        }

        for (auto& [k, v] : postBodyExtras) {
            body.Add({k, v});
        }

        if (opt.auth || conf.auth.size()) {
            body.Add({"access_token", opt.auth.value_or(conf.auth)});
        }

        cpr::Url url{"https://api.stackexchange.com/" + conf.apiVersion + "/" + dest};
        auto res = sess.Post(url, body, conf.userAgent);

        if (auto jsonOpt = checkErrors(res, opt)) {
            if (faulted) {
                conf.reportError(FaultType::RESTORED, "");
            }
            return *jsonOpt;
        }
        faulted = true;

    } while (true);
}

nlohmann::json StackAPI::getRaw(const std::string &dest,
                                const std::map<std::string, std::string>& extraParams,
                                const APIConfigOpt& opt) {

    bool faulted = false;

    do {

        if (opt.autoHandleBackoff.value_or(conf.autoHandleBackoff)) {
            checkBackoff();
        }
        cpr::Parameters body = {
            {"key", conf.apiKey},
            {"site", opt.site.value_or(conf.site)},
            {"pagesize", std::to_string(opt.pageSize.value_or(conf.pageSize))},
            {"page", std::to_string(opt.page.value_or(1))}
        };
        if (opt.filter) {
            body.Add({"filter", *opt.filter});
        }

        for (auto& [k, v] : extraParams) {
            body.Add({k, v});
        }

        if (opt.auth || conf.auth.size()) {
            body.Add({"access_token", opt.auth.value_or(conf.auth)});
        }

        cpr::Url url{"https://api.stackexchange.com/" + conf.apiVersion + "/" + dest};
        auto res = sess.Get(url, body, conf.userAgent);

        if (auto jsonOpt = checkErrors(res, opt)) {
            if (faulted) {
                conf.reportError(FaultType::RESTORED, "");
            }
            return *jsonOpt;
        }
        faulted = true;
    } while (true);

}

void StackAPI::checkBackoff() {
    auto& backoff = conf.backoff;

    if (backoff.secs != 0) {
        auto time = std::chrono::system_clock::now();
        int consumed = std::ceil(
            std::chrono::duration_cast<std::chrono::seconds>(
                time - backoff.timeReceived
            ).count()
        );

        auto wait = backoff.secs - consumed + 2 * conf.backoffStrictnessMultiplier;
        if (wait > 0) {
            this->conf.reportError(FaultType::RATE_LIMIT, "Backoff instructed; waiting " + std::to_string(wait) + " seconds before sending request...");
            std::this_thread::sleep_for(std::chrono::seconds(wait));
        }

        backoff.secs = 0;
    }
}

std::optional<nlohmann::json> StackAPI::checkErrors(cpr::Response& res, const APIConfigOpt& opt) {
    auto status_code = res.status_code;
    bool isHTTPStatus = true;
    if (status_code == 400) { 
        try {
            status_code = nlohmann::json::parse(res.text).at("error_id");
            isHTTPStatus = false;
        } catch (...) {
            // "json" is HTML
            status_code = 500;
        }
    }

    switch (status_code) {
    case 0: {
        if (opt.autoHandleDowntime.value_or(conf.autoHandleDowntime)) {
            spdlog::warn("Host disconnected from the internet. Sleeping 5 minutes...");
            conf.reportError(FaultType::DOWNTIME, "Host seems to be disconnected from the internet. Retrying in 5 minutes");
            std::this_thread::sleep_for(std::chrono::minutes(5));
        } else {
            throw APIException("Connection failed, or your internet connection is down", res.text, res.url.str(), res.status_code, isHTTPStatus);
        }
    } break;
    case 429:
        // Cloudflare bullshit
        if (opt.autoHandleBackoff.value_or(conf.autoHandleBackoff)) {
            spdlog::warn("Cloudflare says no. Sleeping for 5 minutes...");
            conf.reportError(FaultType::CLOUDFLARE, "Cloudflare has blocked your IP. Retrying in 5 minutes.");
            std::this_thread::sleep_for(std::chrono::minutes(5));
        } else {
            throw APIException("Cloudflare blocked the request", res.text, res.url.str(), res.status_code, isHTTPStatus);
        }
    case 500:
    case 503: {
        if (opt.autoHandleDowntime.value_or(conf.autoHandleDowntime)) {
            spdlog::warn("Stack is down. Sleeping 5 minutes...");
            conf.reportError(FaultType::DOWNTIME, "Stack's API appears to be down. Retrying in 5 minutes");
            std::this_thread::sleep_for(std::chrono::minutes(5));
        } else {
            throw APIException("Stack's servers appear to be down", res.text, res.url.str(), res.status_code, isHTTPStatus);
        }
    } break;
    case 502: {
        if (opt.autoHandleBackoff.value_or(conf.autoHandleBackoff)) {
            spdlog::warn("Backoff violated. Sleeping for 5 minutes...");
            conf.reportError(FaultType::RATE_LIMIT, "Backoff violated - sleeping before retrying.");
            std::this_thread::sleep_for(std::chrono::minutes(5));
        } else {
            throw APIException("Backoff violated", res.text, res.url.str(), res.status_code, isHTTPStatus);
        }
    } break;
    case 200: {
        auto json = nlohmann::json::parse(res.text);
        registerBackoff(json);
        return json;
    } break;
    default:
        throw APIException("Likely API error; see errorMessage and statusCode for the type", res.text, res.url.str(), res.status_code, isHTTPStatus);
    }
    return {};
}

void StackAPI::registerBackoff(const nlohmann::json &res) {
    if (res.contains("backoff")) {
        conf.backoff.secs = res.at("backoff").get<int>();
        conf.backoff.timeReceived = std::chrono::system_clock::now();
    }
    if (res.contains("quota_remaining")) {
        res.at("quota_remaining").get_to(conf.remainingQuota);
    }

}

}
