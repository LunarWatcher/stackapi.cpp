#pragma once

#include <string>
#include <vector>
#include "stackapi/data/structs/users/ShallowUser.hpp"
#include "stackapi/data/structs/Types.hpp"
#include "stackapi/data/structs/collectives/Collective.hpp"
#include "stackapi/data/structs/posts/Answer.hpp"
#include "stackapi/data/structs/posts/ClosedDetails.hpp"
#include "stackapi/data/structs/posts/Notice.hpp"
#include "stackapi/data/structs/posts/MigrationInfo.hpp"
#include "stackapi/data/structs/comments/Comment.hpp"

namespace stackapi {

struct Question {
    API_INT accepted_answer_id;
    API_INT answer_count;
    std::vector<Answer> answers;
    std::string body;
    std::string body_markdown;
    API_INT bounty_amount;
    API_DATE bounty_closes_date;
    ShallowUser bounty_user;
    bool can_answer;
    bool can_close;
    bool can_comment;
    bool can_edit;
    bool can_flag;
    bool can_suggest_edit;
    API_INT close_vote_count;
    API_DATE closed_date;
    ClosedDetails closed_details;
    std::string closed_reason;
    std::vector<Collective> collectives;
    API_INT comment_count;
    std::vector<Comment> comments;
    API_DATE community_owned_date;
    std::string content_license;
    API_DATE creation_date;
    API_INT delete_vote_count;
    API_INT down_vote_count;
    bool downvoted ;
    API_INT favorite_count;
    bool favorited ;
    bool is_answered;
    API_DATE last_activity_date;
    API_DATE last_edit_date;
    ShallowUser last_editor;
    std::string link;
    API_DATE locked_date;
    MigrationInfo migrated_from;
    MigrationInfo migrated_to;
    Notice notice;
    ShallowUser owner;
    std::vector<Collective> posted_by_collectives;
    API_DATE protected_date;
    API_INT question_id;
    API_INT reopen_vote_count;
    API_INT score;
    std::string share_link;
    std::vector<std::string> tags;
    std::string title;
    API_INT up_vote_count;
    bool upvoted;
    API_INT view_count;
};

extern void from_json(const nlohmann::json& j, Question& r);

}
