#pragma once

#include <map>
#include <string>
#include <vector>

#include "data/Backoff.hpp"
#include "nlohmann/json_fwd.hpp"
#include <cpr/cpr.h>
#include <nlohmann/json.hpp>
#include <spdlog/spdlog.h>

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
                        const APIConfigOpt& opt = {});

    nlohmann::json getRaw(const std::string& dest,
                        const std::map<std::string, std::string>& extraParams = {},
                        const APIConfigOpt& opt = {});

    template <typename T>
    std::vector<T> get(const std::string& dest,
                        const std::map<std::string, std::string>& extraParams = {},
                        const APIConfigOpt& opt = {}) {

    }

    void checkBackoff();
    void registerBackoff(const nlohmann::json& res);

    Backoff getBackoff() { return conf.backoff; }
    int getRemainingQuota() { return conf.remainingQuota; }
};

}

