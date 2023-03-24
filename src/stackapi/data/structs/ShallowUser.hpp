#pragma once

#include <string>
#include "BadgeCount.hpp"
#include "nlohmann/json_fwd.hpp"

namespace stackapi {

struct ShallowUser {
    int accept_rate;
    int account_id;
    BadgeCount badge_counts;
    std::string display_name;
    std::string link;
    std::string profile_image;
    int reputation;
    int user_id;
    std::string user_type;
};

extern void from_json(const nlohmann::json& j, ShallowUser& r);

}
