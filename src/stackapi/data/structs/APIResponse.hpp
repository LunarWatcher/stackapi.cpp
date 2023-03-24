#pragma once

#include <string>
#include <vector>
#include <nlohmann/json.hpp>


namespace stackapi {

struct APIResponse {
    bool has_more = false;

    int backoff = 0;
    int error_id = 0;
    int page = 1;
    int page_size = 0;

    int quota_max = 0;
    int quota_remaining = 0;
    
    std::string error_message = "";
    std::string error_name = "";
    std::string type = "";

    int total = 0;

    nlohmann::json items = {};
};

extern void from_json(const nlohmann::json& j, APIResponse& r);

}
