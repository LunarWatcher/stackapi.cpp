#pragma once

#include <vector>
#include <string>
#include "CollectiveExternalLink.hpp"
#include "nlohmann/json.hpp"

namespace stackapi {

struct Collective {
    std::string description;
    std::vector<CollectiveExternalLink> collective_external_links;
    std::string link;
    std::string name;
    std::string slug;
    std::vector<std::string> tags;
};

extern void from_json(const nlohmann::json& j, Collective& r);

}
