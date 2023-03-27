#pragma once

#include <string>
#include <vector>
#include <nlohmann/json.hpp>
#include "stackapi/data/structs/Types.hpp"

#define COND_AT(field, dest) if (j.contains(field)) { \
        j.at(field).get_to(dest); \
    }

namespace stackapi {

template <typename T>
struct APIResponse {
    bool has_more = false;

    API_INT backoff = 0;
    API_INT error_id = 0;
    API_INT page = 1;
    API_INT page_size = 0;

    API_INT quota_max = 0;
    API_INT quota_remaining = 0;
    
    std::string error_message = "";
    std::string error_name = "";
    std::string type = "";

    API_INT total = 0;

    std::vector<T> items {};
};

template <typename T>
void from_json(const nlohmann::json& j, APIResponse<T>& r) {
    COND_AT("backoff", r.backoff);
    COND_AT("error_id", r.error_id);
    COND_AT("error_message", r.error_message);
    COND_AT("error_name", r.error_name);
    COND_AT("has_more", r.has_more);
    COND_AT("items", r.items);
    COND_AT("page", r.page);
    COND_AT("page_size", r.page_size);
    COND_AT("quota_max", r.quota_max);
    COND_AT("quota_remaining", r.quota_remaining);
    COND_AT("total", r.total);
    COND_AT("type", r.type);
}

}
