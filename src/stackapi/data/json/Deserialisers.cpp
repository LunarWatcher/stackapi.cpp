#include "stackapi/data/structs/APIResponse.hpp"

#define COND_AT(field, dest) if (j.contains(field)) { \
        j.at(field).get_to(dest); \
    }

namespace stackapi {

void from_json(const nlohmann::json &j, APIResponse &r) {
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
