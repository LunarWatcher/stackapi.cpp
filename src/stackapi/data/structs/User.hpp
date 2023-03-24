#pragma once

#include "BadgeCount.hpp"

namespace stackapi {

struct User {
    std::string about_me;
    int accept_rate;
    int account_id;
    int age;
    int answer_count;

    BadgeCount badge_counts;
    std::vector<std::string> collectives;
    long long creation_date;
    std::string display_name;
    int down_vote_count;
    bool is_employee;
    long long last_access_date;
    long long last_modified_date;
    std::string link;
    std::string location;
    std::string profile_image;
    int question_count;
    int reputation;
    int reputation_change_day;
    int reputation_change_month;
    int reputation_change_quarter;
    int reputation_change_week;
    int reputation_change_year;
    long long timed_penalty_date;
    int up_vote_count;
    int user_id;
    std::string user_type;
    int view_count;
    std::string website_url;
};

extern void from_json(const nlohmann::json& j, User& r);

}
