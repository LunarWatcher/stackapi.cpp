#include "StackAPI.hpp"

#include <stdexcept>

namespace stackapi {

StackAPI::StackAPI(const APIConfig& conf) : conf(conf) {
    if (conf.apiKey == "") {
        throw std::runtime_error("Misconfiguration: an API key is required.");
    }
}

}
