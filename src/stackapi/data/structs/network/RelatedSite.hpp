#pragma once

#include <nlohmann/json.hpp>
#include <string>

namespace stackapi {

struct RelatedSite {
    std::string api_site_parameter;
    std::string name;
    std::string relation;
    std::string site_url;
};

extern void from_json(const nlohmann::json& j, RelatedSite& r);

}
