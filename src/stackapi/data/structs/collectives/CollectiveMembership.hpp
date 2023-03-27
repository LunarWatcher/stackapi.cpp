#pragma once

#include <string>
#include <nlohmann/json.hpp>

#include "Collective.hpp"

namespace stackapi {

struct CollectiveMembership {
    Collective collective;
    std::string role;
};

extern void from_json(const nlohmann::json& j, CollectiveMembership& r);

}
