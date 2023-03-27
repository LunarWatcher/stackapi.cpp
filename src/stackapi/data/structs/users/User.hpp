#pragma once

#include "BadgeCount.hpp"
#include "stackapi/data/structs/collectives/CollectiveMembership.hpp"
#include "stackapi/data/structs/Types.hpp"

namespace stackapi {

struct User {
    std::string about_me;
    API_INT accept_rate;
    API_INT account_id;
    API_INT age;
    API_INT answer_count;

    BadgeCount badge_counts;
    std::vector<CollectiveMembership> collectives;
    API_DATE creation_date;
    std::string display_name;
    API_INT down_vote_count;
    bool is_employee;
    API_DATE last_access_date;
    API_DATE last_modified_date;
    std::string link;
    std::string location;
    std::string profile_image;
    API_INT question_count;
    API_INT reputation;
    API_INT reputation_change_day;
    API_INT reputation_change_month;
    API_INT reputation_change_quarter;
    API_INT reputation_change_week;
    API_INT reputation_change_year;
    API_DATE timed_penalty_date;
    API_INT up_vote_count;
    API_INT user_id;
    std::string user_type;
    API_INT view_count;
    std::string website_url;
};

extern void from_json(const nlohmann::json& j, User& r);

}
