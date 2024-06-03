#pragma once

#include "spdlog/spdlog.h"
#include <exception>
#include <string>

#include <stackapi/data/structs/Types.hpp>

namespace stackapi {

class APIException : public std::exception {
public:
    std::string message;
    /**
     * message usually contains API-provided messages, while errorMessage contains a message straight from the API.
     *
     * Note that this may or may not be useful. Not all faults return JSON
     */
    std::string errorMessage;
    std::string url;
    API_INT statusCode;
    bool isHTTPStatus;

    APIException(const std::string& message, const std::string& errorMessage, const std::string& url, API_INT statusCode,
                 bool isHTTPStatus)
        : message(message), url(url), errorMessage(errorMessage), statusCode(statusCode), isHTTPStatus(isHTTPStatus) {
        // TODO: Does this make sense?
        spdlog::error("{}: {} (status code: {} on invoked URL {})", message, errorMessage, statusCode, url);        
    }

    char* what() {
        return message.data();
    }
};

}
