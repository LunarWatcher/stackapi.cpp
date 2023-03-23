#include "StackAPI.hpp"

#include <stdexcept>

namespace stackapi {

StackAPI::StackAPI(const APIConfig& conf, bool dryRun) : conf(conf), dryRun(dryRun) {
    if (conf.apiKey == "") {
        throw std::runtime_error("Misconfiguration: an API key is required.");
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
