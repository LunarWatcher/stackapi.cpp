#pragma once

#include <map>
#include <string>
#include <vector>

#include "data/Backoff.hpp"
#include "nlohmann/json_fwd.hpp"
#include "stackapi/data/structs/APIResponse.hpp"
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

    /**
     * Backoff calculations have two seconds added for good measure.
     * Those two seconds are multiplied by this value.
     *
     * If it's 0, there is no addition to the expected backoff time. This is
     * not recommended, as this is much more likely to lead to throttle
     * violations. This value can be increased for multi-process applications
     * where thread safety (not currently implemented anyway) isn't enough.
     */
    int backoffStrictnessMultiplier = 1;

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
public:
    APIConfig conf;
    /**
     * Utility control variable.
     *
     * This is never set to anything but false by the library. Its primary intended use is to allow for non-request
     * testing in applications.
     */
    bool dryRun = false;

    StackAPI(const APIConfig& conf, bool dryRun = false);

    nlohmann::json postRaw(const std::string& dest,
                        const std::map<std::string, std::string>& postBodyExtras = {},
                        const APIConfigOpt& opt = {});

    template <typename T>
    APIResponse<T> post(const std::string& dest,
                        const std::map<std::string, std::string>& postBodyExtras = {},
                        const APIConfigOpt& opt = {}) {
        auto raw = postRaw(dest, postBodyExtras, opt);
        return raw.get<APIResponse<T>>();
    }

    nlohmann::json getRaw(const std::string& dest,
                        const std::map<std::string, std::string>& extraParams = {},
                        const APIConfigOpt& opt = {});

    template <typename T>
    APIResponse<T> get(const std::string& dest,
                        const std::map<std::string, std::string>& extraParams = {},
                        const APIConfigOpt& opt = {}) {
        auto raw = getRaw(dest, extraParams, opt);
        return raw.get<APIResponse<T>>();
    }

    /**
     * Checks for a backoff, and sleeps if necessary.
     */
    void checkBackoff();

    /**
     * Registers the backoff from a given JSON response.
     * This automatically checks if the backoff key is present
     *
     * Also, the name is partly a lie. It also st ores the remaining quota in conf. 
     */
    void registerBackoff(const nlohmann::json& res);

    Backoff getBackoff() { return conf.backoff; }
    int getRemainingQuota() { return conf.remainingQuota; }
};

}

