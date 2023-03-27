#pragma once

#include <nlohmann/json.hpp>
#include <string>


#include "stackapi/data/structs/Types.hpp"
#include "stackapi/data/structs/users/ShallowUser.hpp"

namespace stackapi {

struct Comment {
    std::string body;
    std::string body_markdown;
    bool can_flag;
    API_INT comment_id;
    std::string content_license;
    API_DATE creation_date;
    bool edited;
    std::string link;
    ShallowUser owner;
    API_INT post_id;
    std::string post_type;
    ShallowUser reply_to_user;
    API_INT score;
    bool upvoted;
};

extern void from_json(const nlohmann::json& j, Comment& r);

}
