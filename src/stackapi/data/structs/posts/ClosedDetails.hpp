#pragma once

#include <nlohmann/json.hpp>
#include <string>
#include <vector>

#include "stackapi/data/structs/users/ShallowUser.hpp"
#include "OriginalQuestion.hpp"

namespace stackapi {

struct ClosedDetails {
    std::vector<ShallowUser> by_users;
    std::string description;
    bool on_hold;
    std::vector<OriginalQuestion> original_questions;
    std::string reason;
};

extern void from_json(const nlohmann::json& j, ClosedDetails& r);

}
