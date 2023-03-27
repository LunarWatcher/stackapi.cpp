#pragma once

#include "stackapi/data/structs/comments/Comment.hpp"
#include "stackapi/data/structs/users/ShallowUser.hpp"
#include "stackapi/data/structs/collectives/Collective.hpp"
#include <vector>
#include <string>
#include "stackapi/data/structs/Types.hpp"

namespace stackapi {

// Strictly speaking, this _could_ be merged into both Question and Answer to reduce some overhead, but... meh.
// Doing so doesn't simplify the deserialisation anyway, and just adds another layer of overhead.
// Also, post_id isn't the name used in both Question and Answer, so it really does nothing.
//
// Shit API design IMO, but I didn't make it. I'm just masochistic enough to make an adapter for it.
// There's... a lot of questionable decisions.
struct Post {
    std::string body;
    std::string body_markdown;
    std::vector<Collective> collectives;
    API_INT comment_count;
    std::vector<Comment> comments;
    std::string content_license;
    API_DATE creation_date;
    API_INT down_vote_count;
    bool downvoted;
    API_DATE last_activity_date;
    API_DATE last_edit_date;
    ShallowUser owner;
    API_INT post_id;
    std::string post_type;
    std::vector<Collective> posted_by_collectives;
    API_INT score;
    std::string share_link;
    std::string title;
    API_INT up_vote_count;
    bool upvoted;
};

extern void from_json(const nlohmann::json& j, Post& r);

}
