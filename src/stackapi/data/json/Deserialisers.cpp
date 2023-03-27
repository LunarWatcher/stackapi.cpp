#include <nlohmann/json.hpp>

#include "stackapi/data/structs/posts/ClosedDetails.hpp"
#include "stackapi/data/structs/posts/Notice.hpp"
#include "stackapi/data/structs/posts/OriginalQuestion.hpp"
#include "stackapi/data/structs/posts/Post.hpp"
#include "stackapi/data/structs/posts/Question.hpp"
#include "stackapi/data/structs/users/BadgeCount.hpp"
#include "stackapi/data/structs/comments/Comment.hpp"
#include "stackapi/data/structs/NullStruct.hpp"
#include "stackapi/data/structs/users/ShallowUser.hpp"
#include "stackapi/data/structs/users/User.hpp"
#include "stackapi/data/structs/collectives/Collective.hpp"
#include "stackapi/data/structs/collectives/CollectiveExternalLink.hpp"
#include "stackapi/data/structs/collectives/CollectiveMembership.hpp"
#include "stackapi/data/structs/collectives/CollectiveRecommendation.hpp"
#include "stackapi/data/structs/network/RelatedSite.hpp"
#include "stackapi/data/structs/network/Site.hpp"
#include "stackapi/data/structs/network/Styling.hpp"
#include "stackapi/data/structs/posts/Answer.hpp"
#include "stackapi/data/structs/posts/MigrationInfo.hpp"


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

void from_json(const nlohmann::json& j, Collective& r) {
    COND_AT("description", r.description);
    COND_AT("collective_external_links", r.collective_external_links);
    COND_AT("link", r.link);
    COND_AT("name", r.name);
    COND_AT("slug", r.slug);
    COND_AT("tags", r.tags);
}

void from_json(const nlohmann::json &j, CollectiveExternalLink &r) {
    COND_AT("link", r.link);
    COND_AT("type", r.type);
}

void from_json(const nlohmann::json &j, CollectiveMembership &r) {
    COND_AT("collective", r.collective);
    COND_AT("role", r.role);
}

void from_json(const nlohmann::json &j, Styling &r) {
    COND_AT("link_color", r.link_color);
    COND_AT("tag_background_color", r.tag_background_color);
    COND_AT("tag_foreground_color", r.tag_foreground_color);
}

void from_json(const nlohmann::json &j, Site &r) {
    COND_AT("aliases", r.aliases);
    COND_AT("api_site_parameter", r.api_site_parameter);
    COND_AT("audience", r.audience);
    COND_AT("closed_beta_date", r.closed_beta_date);
    COND_AT("favicon_url", r.favicon_url);
    COND_AT("high_resolution_icon_url", r.high_resolution_icon_url);
    COND_AT("icon_url", r.icon_url);

    COND_AT("launch_date", r.launch_date);
    COND_AT("logo_url", r.logo_url);
    COND_AT("markdown_extensions", r.markdown_extensions);
    COND_AT("name", r.name);
    COND_AT("open_beta_date", r.open_beta_date);
    COND_AT("related_sites", r.related_sites);
    COND_AT("site_state", r.site_state);
    COND_AT("site_type", r.site_type);
    COND_AT("site_url", r.site_url);
    COND_AT("styling", r.styling);
    COND_AT("twitterAccount", r.twitterAccount);
}

void from_json(const nlohmann::json &j, MigrationInfo &r) {
    COND_AT("on_date", r.on_date);
    COND_AT("origin", r.origin);
    COND_AT("question_id", r.question_id);
}

void from_json(const nlohmann::json &j, CollectiveRecommendation &r) {
    COND_AT("collective", r.collective);
    COND_AT("creation_date", r.creation_date);
}

void from_json(const nlohmann::json &j, RelatedSite &r) {
    COND_AT("api_site_parameter", r.api_site_parameter);
    COND_AT("name", r.name);
    COND_AT("relation", r.relation);
    COND_AT("site_url", r.site_url);
}

void from_json(const nlohmann::json& j, Answer& r) {
    COND_AT("accepted", r.accepted);
    COND_AT("answer_id", r.answer_id);
    COND_AT("awarded_bounty_amount", r.awarded_bounty_amount);
    COND_AT("awarded_bounty_users", r.awarded_bounty_users);
    COND_AT("body", r.body);
    COND_AT("body_markdown", r.body_markdown);

    COND_AT("can_comment", r.can_comment);
    COND_AT("can_edit", r.can_edit);
    COND_AT("can_flag", r.can_flag);
    COND_AT("can_suggest_edit", r.can_suggest_edit);
    COND_AT("collectives", r.collectives);
    COND_AT("comment_count", r.comment_count);
    COND_AT("comments", r.comments);
    COND_AT("community_owned_date", r.community_owned_date);
    COND_AT("content_license", r.content_license);
    COND_AT("creation_date", r.creation_date);
    COND_AT("down_vote_count", r.down_vote_count);
    COND_AT("downvoted", r.downvoted);
    COND_AT("is_accepted", r.is_accepted);

    COND_AT("last_edit_date", r.last_edit_date);
    COND_AT("last_editor", r.last_editor);
    COND_AT("link", r.link);
    COND_AT("locked_date", r.locked_date);
    COND_AT("owner", r.owner);
    COND_AT("posted_by_collectives", r.posted_by_collectives);
    COND_AT("question_id", r.question_id);
    COND_AT("collective_recommendations", r.collective_recommendations);
    COND_AT("score", r.score);
    COND_AT("share_link", r.share_link);
    COND_AT("tags", r.tags);
    COND_AT("title", r.title);
    COND_AT("up_vote_count", r.up_vote_count);
    COND_AT("upvoted", r.upvoted);
}

void from_json(const nlohmann::json & j, Post &r) {
    COND_AT("body", r.body);
    COND_AT("body_markdown", r.body_markdown);
    COND_AT("collectives", r.collectives);
    COND_AT("comment_count", r.comment_count);
    COND_AT("comments", r.comments);
    COND_AT("content_license", r.content_license);
    COND_AT("creation_date", r.creation_date);
    COND_AT("down_vote_count", r.down_vote_count);
    COND_AT("downvoted", r.downvoted);
    COND_AT("last_activity_date", r.last_activity_date);
    COND_AT("last_edit_date", r.last_edit_date);
    COND_AT("owner", r.owner);
    COND_AT("post_id", r.post_id);
    COND_AT("post_type", r.post_type);
    COND_AT("posted_by_collectives", r.posted_by_collectives);
    COND_AT("score", r.score);
    COND_AT("share_link", r.share_link);
    COND_AT("title", r.title);
    COND_AT("up_vote_count", r.up_vote_count);
    COND_AT("upvoted", r.upvoted);
}

void from_json(const nlohmann::json &j, Notice &r) {
    COND_AT("body", r.body);
    COND_AT("creation_date", r.creation_date);
    COND_AT("owner_user_id", r.owner_user_id);
}

void from_json(const nlohmann::json &j, ClosedDetails &r) {
    COND_AT("by_users", r.by_users);
    COND_AT("description", r.description);
    COND_AT("on_hold", r.on_hold);
    COND_AT("original_questions", r.original_questions);
    COND_AT("reason", r.reason);
}

void from_json(const nlohmann::json &j, Question &r) {
    COND_AT("accepted_answer_id", r.accepted_answer_id);
    COND_AT("answer_count", r.answer_count);
    COND_AT("answers", r.answers);
    COND_AT("body", r.body);
    COND_AT("body_markdown", r.body_markdown);
    COND_AT("bounty_amount", r.bounty_amount);
    COND_AT("bounty_closes_date", r.bounty_closes_date);
    COND_AT("bounty_user", r.bounty_user);
    COND_AT("can_answer", r.can_answer);
    COND_AT("can_close", r.can_close);
    COND_AT("can_comment", r.can_comment);
    COND_AT("can_edit", r.can_edit);
    COND_AT("can_flag", r.can_flag);
    COND_AT("can_suggest_edit", r.can_suggest_edit);
    COND_AT("close_vote_count", r.close_vote_count);
    COND_AT("closed_date", r.closed_date);
    COND_AT("closed_details", r.closed_details);
    COND_AT("closed_reason", r.closed_reason);
    COND_AT("collectives", r.collectives);
    COND_AT("comment_count", r.comment_count);
    COND_AT("comments", r.comments);
    COND_AT("community_owned_date", r.community_owned_date);
    COND_AT("content_license", r.content_license);
    COND_AT("creation_date", r.creation_date);
    COND_AT("delete_vote_count", r.delete_vote_count);
    COND_AT("down_vote_count", r.down_vote_count);
    COND_AT("downvoted", r.downvoted);
    COND_AT("favorite_count", r.favorite_count);
    COND_AT("favorited", r.favorited);
    COND_AT("is_answered", r.is_answered);
    COND_AT("last_activity_date", r.last_activity_date);
    COND_AT("last_edit_date", r.last_edit_date);
    COND_AT("last_editor", r.last_editor);
    COND_AT("link", r.link);
    COND_AT("locked_date", r.locked_date);
    COND_AT("migrated_from", r.migrated_from);
    COND_AT("migrated_to", r.migrated_to);
    COND_AT("notice", r.notice);
    COND_AT("owner", r.owner);
    COND_AT("posted_by_collectives", r.posted_by_collectives);
    COND_AT("protected_date", r.protected_date);
    COND_AT("question_id", r.question_id);
    COND_AT("reopen_vote_count", r.reopen_vote_count);
    COND_AT("score", r.score);
    COND_AT("share_link", r.share_link);
    COND_AT("tags", r.tags);
    COND_AT("title", r.title);
    COND_AT("up_vote_count", r.up_vote_count);
    COND_AT("upvoted", r.upvoted);
    COND_AT("view_count", r.view_count);

}

void from_json(const nlohmann::json &j, OriginalQuestion &r) {
    COND_AT("accepted_answer_id", r.accepted_answer_id);
    COND_AT("answer_count", r.answer_count);
    COND_AT("question_id", r.question_id);
    COND_AT("title", r.title);
}

// Don't ask. Just pretend this doesn't exist.
#pragma optimize("", off)
void from_json(const nlohmann::json& j, NullStruct& r) {}
#pragma optimize("", on)

}
