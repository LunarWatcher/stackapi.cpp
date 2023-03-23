#pragma once

#include <map>
#include <string>
#include <vector>

#include "data/Backoff.hpp"
#include "nlohmann/json_fwd.hpp"
#include <cpr/cpr.h>
#include <nlohmann/json.hpp>

namespace stackapi {

struct APIConfig {
    std::string apiKey = "";
    std::string auth = "";
    std::string site = "";

    std::string apiVersion = "2.3";
    unsigned int pageSize = 100;
    int remainingQuota = 0;

    bool autoHandleBackoff = true;
    bool autoHandleDowntime = true;

    Backoff backoff = { 0, std::chrono::system_clock::now() };
};

struct APIConfigOpt {
    std::optional<std::string> auth;
    std::optional<std::string> site;
    std::optional<std::string> filter;

    std::optional<unsigned int> page;
    std::optional<unsigned int> pageSize;

    std::optional<bool> autoHandleBackoff;
    std::optional<bool> autoHandleDowntime;
};

class StackAPI {
private:
    APIConfig conf;

public:
    /**
     * Utility control variable.
     *
     * This is never set to anything but false by the library. Its primary intended use is to allow for non-request
     * testing in applications.
     */
    bool dryRun = false;

    StackAPI(const APIConfig& conf, bool dryRun = false);

    nlohmann::json post(const std::string& dest,
                        const std::map<std::string, std::string>& postBodyExtras = {},
                        const APIConfigOpt& opt = {}) {
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

            if (opt.auth || conf.auth.size()) {
                body.Add({"access_token", opt.auth.value_or(conf.auth)});
            }

            cpr::Url url{"https://api.stackexchange.com/" + conf.apiVersion + "/" + dest};
            auto res = cpr::Post(url, body);

            switch (res.status_code) {
            case 0: {

            } break;
            case 500: {
                if (opt.autoHandleDowntime.value_or(conf.autoHandleDowntime)) {

                } else {
                    throw std::runtime_error("Stack's servers are down: " + res.text + "; " + res.error.message);
                }
            } break;
            case 200: {
                auto json = nlohmann::json::parse(res.text);

            } break;
            default:
                break;
            }
            if (res.status_code == 0) {
            } else if (res.status_code != 200) {
                try {
                    auto json = nlohmann::json::parse(res.text);
                } catch (...) {
                    
                }
            } else {
                auto json = nlohmann::json::parse(res.text);
                if (json.contains("backoff")) {
                    conf.backoff.secs = json["backoff"].get<int>();

                }
            }
        } while (true);
    }

    void checkBackoff();
    void registerBackoff(const nlohmann::json& res);

    Backoff getBackoff() { return conf.backoff; }
    int getRemainingQuota() { return conf.remainingQuota; }
};

}

