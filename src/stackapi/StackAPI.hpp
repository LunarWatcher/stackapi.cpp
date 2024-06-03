#pragma once

#include <map>
#include <string>
#include <vector>

#include "cpr/session.h"
#include "cpr/user_agent.h"
#include "data/Backoff.hpp"
#include "nlohmann/json_fwd.hpp"
#include "stackapi/data/structs/APIResponse.hpp"
#include "stackapi/data/web/MTSession.hpp"
#include <cpr/cpr.h>
#include <nlohmann/json.hpp>
#include <spdlog/spdlog.h>

namespace stackapi {

enum class FaultType {
    DOWNTIME,
    CLOUDFLARE,
    RATE_LIMIT,
    OTHER,
    /**
     * Special code that doesn't denote a fault, but notes that whatever fault was previously reported has been fixed.
     * Note that if FaultType == RESTORED, then message == "", so it shouldn't be displayed directly.
     */
    RESTORED
};

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
     * This is one of the more aggressive defaults, but there is a good reason for it:
     * 1. 404s during development are easier to see; ctrl-c, fix, continue on your merry way.
     * 2. 404s are often a symptom of downtime, as the server is on its last breath
     *    and just able to spew out a 404, but isn't alive enough to tell it's committing die.
     *
     * If this is enabled, all 404s result in the normal downtime recovery system.
     * If this is disabled, a single web request is made to api.stackexchange.com. If it's fine,
     * the error recovery throws under the assumption it's a dev error. Otherwise, recovery
     * commences.
     */
    bool treat404AsDowntime = true;

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

    cpr::UserAgent userAgent = "StackAPIUnannouncedUser/git";

    /**
     * Special callback invoked when dealing with backoff or downtime. 
     * Note that this is only invoked when autoHandleBackoff and/or autoHandleDowntime is true.
     * If, for example, automatically handling backoff, but autoHandleBackoff is false, an
     * exception is thrown instead. This callback is meant to be coupled with the built-in
     * handling systems.
     *
     * Note that FaultType doesn't 1:1 correspond with the different config options. Notably,
     * Cloudflare is treated as backoff, while RATE_LIMIT just refers to the standard backoff.
     * The categories are meant to be used to separate issues you do or don't care about handling.
     *
     * This function is primarily aimed at two things:
     * 1. Supplying fault notification systems with information; for the most part, this applies to
     *    CLOUDFLARE, as cloudflare blocking is downtime, while rate limit-based backoff is more expected.
     *
     *    This is primarily aimed at bot and bot management, and to make it easier for me to know when to
     *    poke SE with another complaint about Cloudflare being dumb again
     * 2. Supplying information to an end-user in, for example, a desktop application, where the auto-handling
     *    is still desirable behaviour, but where the user also should be notified
     *
     * Note that this function is not required. If you don't care about handling any of these, set the value to
     * nullptr. 
     *
     * Also note that not everything reported is an error. This function is also invoked when doing preventative
     * backoff waiting, and not only when SE blocks the request. This is also reported under FaultType::RATE_LIMIT,
     * with a message explaining the problem. I have not decided if it makes sense to separate these or not.
     */
    std::function<void(FaultType, const std::string& message)> errorCallback = nullptr;

    Backoff backoff = { 0, std::chrono::system_clock::now() };

    void reportError(FaultType type, const std::string& message) const {
        if (errorCallback) {
            errorCallback(type, message);
        }
    }

};

struct APIConfigOpt {
    std::optional<std::string> auth;
    std::optional<std::string> site;
    std::optional<std::string> filter;

    std::optional<unsigned int> page;
    std::optional<unsigned int> pageSize;

    std::optional<bool> autoHandleBackoff;
    std::optional<bool> autoHandleDowntime;
    std::optional<bool> treat404AsDowntime;

};

class StackAPI {
public:
    APIConfig conf;
    MTSession sess;

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

    std::optional<nlohmann::json> checkErrors(cpr::Response& res, const APIConfigOpt& opt);

    Backoff getBackoff() { return conf.backoff; }
    int getRemainingQuota() { return conf.remainingQuota; }
};

}

