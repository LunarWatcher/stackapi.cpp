#pragma once

#include <string>
#include "BadgeCount.hpp"
#include "nlohmann/json.hpp"
#include "stackapi/data/structs/Types.hpp"

namespace stackapi {

struct ShallowUser {
    API_INT accept_rate;
    API_INT account_id;
    BadgeCount badge_counts;
    std::string display_name;
    std::string link;
    std::string profile_image;
    API_INT reputation;
    API_INT user_id;
    std::string user_type;
};

extern void from_json(const nlohmann::json& j, ShallowUser& r);

}
