#pragma once

#include <nlohmann/json.hpp>
#include <string>

#include "ShallowUser.hpp"

namespace stackapi {

struct Comment {
    std::string body;
    std::string body_markdown;
    bool can_flag;
    int comment_id;
    std::string content_license;
    long long creation_date;
    bool edited;
    std::string link;
    ShallowUser owner;
    int post_id;
    std::string post_type;
    ShallowUser reply_to_user;
    int score;
    bool upvoted;
};

extern void from_json(const nlohmann::json& j, Comment& r);

}
