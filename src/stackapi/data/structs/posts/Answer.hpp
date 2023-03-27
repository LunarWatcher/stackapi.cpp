#pragma once

#include <nlohmann/json.hpp>
#include <string>
#include <vector>

#include "stackapi/data/structs/Comment.hpp"
#include "stackapi/data/structs/ShallowUser.hpp"
#include "stackapi/data/structs/collectives/Collective.hpp"
#include "stackapi/data/structs/collectives/CollectiveRecommendation.hpp"
#include "stackapi/data/structs/Types.hpp"

namespace stackapi {

struct Answer {
    bool accepted;
    API_INT answer_id;
    API_INT awarded_bounty_amount;
    API_INT awarded_bounty_users;
    std::string body;
    std::string body_markdown;

    bool can_comment;
    bool can_edit;
    bool can_flag;
    bool can_suggest_edit;
    std::vector<Collective> collectives;
    API_INT comment_count;
    std::vector<Comment> comments;
    API_DATE community_owned_date;
    std::string content_license;
    API_DATE creation_date;
    API_INT down_vote_count;
    bool downvoted;
    bool is_accepted;

    API_DATE last_edit_date;
    ShallowUser lastEditor;
    std::string link;
    API_DATE locked_date;
    ShallowUser owner;
    std::vector<Collective> posted_by_collectives;
    API_INT question_id;
    std::vector<CollectiveRecommendation> collective_recommendations;
    API_INT score;
    std::string share_link;
    std::vector<std::string> tags;
    std::string title;
    API_INT up_vote_count;
    bool upvoted;
    

};

extern void from_json(const nlohmann::json& j, Answer& r);


}
