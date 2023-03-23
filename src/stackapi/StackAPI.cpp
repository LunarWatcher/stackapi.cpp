#include "StackAPI.hpp"

#include <stdexcept>

namespace stackapi {

StackAPI::StackAPI(const APIConfig& conf, bool dryRun) : conf(conf), dryRun(dryRun) {
    if (conf.apiKey == "") {
        throw std::runtime_error("Misconfiguration: an API key is required.");
    }
}

nlohmann::json StackAPI::post(const std::string& dest,
                    const std::map<std::string, std::string>& postBodyExtras,
                    const APIConfigOpt& opt) {
    if (dryRun) {
        return {};
    }
    size_t count = 0;
    do {
        if (opt.autoHandleBackoff.value_or(conf.autoHandleBackoff)) {
            checkBackoff();
        }
        cpr::Payload body = {
            {"key", conf.apiKey},
            {"site", opt.site.value_or(conf.site)}
        };

        for (auto& [k, v] : postBodyExtras) {
            body.Add({k, v});
        }

        if (opt.auth || conf.auth.size()) {
            body.Add({"access_token", opt.auth.value_or(conf.auth)});
        }

        cpr::Url url{"https://api.stackexchange.com/" + conf.apiVersion + "/" + dest};
        auto res = cpr::Post(url, body);

        switch (res.status_code) {
        case 0: {
            if (opt.autoHandleDowntime.value_or(conf.autoHandleDowntime)) {
                spdlog::warn("Host disconnected from the internet. Sleeping 5 minutes...");
                std::this_thread::sleep_for(std::chrono::minutes(5));
            } else {
                throw std::runtime_error("Connection failed or internet dead (probably the latter): " + res.text + "; " + res.error.message);
            }
        } break;
        case 500: {
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
            throw std::runtime_error("Unhandled status code: " + std::to_string(res.status_code));
        }

    } while (true);
}

nlohmann::json StackAPI::getRaw(const std::string &dest,
                                const std::map<std::string, std::string>& extraParams,
                                const APIConfigOpt& opt) {
    if (dryRun) {
        return;
    }
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

        auto wait = backoff.secs - consumed + 2;
        if (wait > 0) {
            std::this_thread::sleep_for(std::chrono::seconds(wait));
        }

        backoff.secs = 0;
    }
}

void StackAPI::registerBackoff(const nlohmann::json &res) {
    if (res.contains("backoff")) {
        conf.backoff.secs = res.at("backoff").get<int>();
        conf.backoff.timeReceived = std::chrono::system_clock::now();
    }
}

}
