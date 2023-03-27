#pragma once

#include "nlohmann/json.hpp"
#include <string>

namespace stackapi {

struct CollectiveExternalLink {
    std::string link;
    std::string type;
};

extern void from_json(const nlohmann::json& j, CollectiveExternalLink& r);

}
