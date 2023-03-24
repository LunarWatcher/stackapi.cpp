#include "stackapi/data/structs/BadgeCount.hpp"
#include "stackapi/data/structs/Comment.hpp"
#include "stackapi/data/structs/NullStruct.hpp"
#include "stackapi/data/structs/ShallowUser.hpp"
#include "stackapi/data/structs/User.hpp"


#define COND_AT(field, dest) if (j.contains(field)) { \
        j.at(field).get_to(dest); \
    }

namespace stackapi {

void from_json(const nlohmann::json& j, BadgeCount& r) {
    COND_AT("bronze", r.bronze);
    COND_AT("silver", r.silver);
    COND_AT("gold", r.gold);
}


void from_json(const nlohmann::json& j, Comment& r) {
    COND_AT("body", r.body);
    COND_AT("body_markdown", r.body_markdown);
    COND_AT("can_flag", r.can_flag);
    COND_AT("comment_id", r.comment_id);
    COND_AT("content_license", r.content_license);
    COND_AT("creation_date", r.creation_date);
    COND_AT("edited", r.edited);
    COND_AT("link", r.link);
    COND_AT("owner", r.owner);
    COND_AT("post_id", r.post_id);
    COND_AT("post_type", r.post_type);
    COND_AT("reply_to_user", r.reply_to_user);
    COND_AT("score", r.score);
    COND_AT("upvoted", r.upvoted);
}

void from_json(const nlohmann::json& j, ShallowUser& r) {
    COND_AT("accept_rate", r.accept_rate);
    COND_AT("account_id", r.account_id);
    COND_AT("badge_counts", r.badge_counts);
    COND_AT("display_name", r.display_name);
    COND_AT("link", r.link);
    COND_AT("profile_image", r.profile_image);
    COND_AT("reputation", r.reputation);
    COND_AT("user_id", r.user_id);
    COND_AT("user_type", r.user_type);
}

void from_json(const nlohmann::json& j, User& r) {
    COND_AT("about_me", r.about_me);
    COND_AT("accept_rate", r.accept_rate);
    COND_AT("account_id", r.account_id);
    COND_AT("age", r.age);
    COND_AT("answer_count", r.answer_count);

    COND_AT("badge_counts", r.badge_counts);
    COND_AT("collectives", r.collectives);
    COND_AT("creation_date", r.creation_date);
    COND_AT("display_name", r.display_name);
    COND_AT("down_vote_count", r.down_vote_count);
    COND_AT("is_employee", r.is_employee);
    COND_AT("last_access_date", r.last_access_date);
    COND_AT("last_modified_date", r.last_modified_date);
    COND_AT("link", r.link);
    COND_AT("location", r.location);
    COND_AT("profile_image", r.profile_image);
    COND_AT("question_count", r.question_count);
    COND_AT("reputation", r.reputation);
    COND_AT("reputation_change_day", r.reputation_change_day);
    COND_AT("reputation_change_month", r.reputation_change_month);
    COND_AT("reputation_change_quarter", r.reputation_change_quarter);
    COND_AT("reputation_change_week", r.reputation_change_week);
    COND_AT("reputation_change_year", r.reputation_change_year);
    COND_AT("timed_penalty_date", r.timed_penalty_date);
    COND_AT("up_vote_count", r.up_vote_count);
    COND_AT("user_id", r.user_id);
    COND_AT("user_type", r.user_type);
    COND_AT("view_count", r.view_count);
    COND_AT("website_url", r.website_url);
}

// Don't ask. Just pretend this doesn't exist.
#pragma optimize("", off)
void from_json(const nlohmann::json& j, NullStruct& r) {}
#pragma optimize("", on)

}
