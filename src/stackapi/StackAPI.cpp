#include "StackAPI.hpp"

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
            return *jsonOpt;
        }

    } while (true);
}

nlohmann::json StackAPI::getRaw(const std::string &dest,
                                const std::map<std::string, std::string>& extraParams,
                                const APIConfigOpt& opt) {

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
            return *jsonOpt;
        }
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
            std::this_thread::sleep_for(std::chrono::seconds(wait));
        }

        backoff.secs = 0;
    }
}

std::optional<nlohmann::json> StackAPI::checkErrors(cpr::Response& res, const APIConfigOpt& opt) {
    auto status_code = res.status_code;
    if (status_code == 400) { 
        try {
            status_code = nlohmann::json::parse(res.text).at("error_id");
        } catch (...) {
            // "json" is HTML
            status_code = 500;
        }
    }

    switch (status_code) {
    case 0: {
        if (opt.autoHandleDowntime.value_or(conf.autoHandleDowntime)) {
            spdlog::warn("Host disconnected from the internet. Sleeping 5 minutes...");
            std::this_thread::sleep_for(std::chrono::minutes(5));
        } else {
            throw std::runtime_error("Connection failed or internet dead (probably the latter): " + res.text + "; " + res.error.message);
        }
    } break;
    case 500:
    case 503: {
        if (opt.autoHandleDowntime.value_or(conf.autoHandleDowntime)) {
            spdlog::warn("Stack is down. Sleeping 5 minutes...");
            std::this_thread::sleep_for(std::chrono::minutes(5));
        } else {
            throw std::runtime_error("Stack's servers are down: " + res.text + "; " + res.error.message);
        }
    } break;
    case 502: {
        if (opt.autoHandleBackoff.value_or(conf.autoHandleBackoff)) {
            spdlog::warn("Backoff violated. Sleeping for 5 minutes...");
            std::this_thread::sleep_for(std::chrono::minutes(5));
        } else {
            throw std::runtime_error("Backoff violated. " + res.text + "; " + res.error.message);
        }
    } break;
    case 200: {
        auto json = nlohmann::json::parse(res.text);
        registerBackoff(json);
        return json;
    } break;
    default:
        throw std::runtime_error("Unhandled status code: " + std::to_string(res.status_code) + "; " + res.text + "; " + res.error.message + " on URL " + res.url.str());
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
