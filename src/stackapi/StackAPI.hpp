#pragma once

#include <string>
#include <vector>

#include "data/Backoff.hpp"

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

    Backoff backoff = { 0, 0.0 };
};

class StackAPI {
private:
    APIConfig conf;

public:
    bool dryRun = false;

    StackAPI(const APIConfig& conf, bool dryRun = false);

    template <typename T>
    std::vector<T> post(const std::string& dest, const std::string& filter = "") {
        if (dryRun) {
            return {};
        }

        

    }

    Backoff getBackoff() { return conf.backoff; }
    int getRemainingQuota() { return conf.remainingQuota; }
};

}

