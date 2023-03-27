#pragma once

#include <string>
#include <nlohmann/json.hpp>
#include "RelatedSite.hpp"
#include "Styling.hpp"
#include "stackapi/data/structs/Types.hpp"

namespace stackapi {

struct Site {
    std::vector<std::string> aliases;
    std::string api_site_parameter;
    std::string audience;
    API_DATE closed_beta_date;
    std::string favicon_url;
    std::string high_resolution_icon_url;
    std::string icon_url;

    API_DATE launch_date;
    std::string logo_url;
    std::vector<std::string> markdown_extensions;
    std::string name;
    API_DATE open_beta_date;
    std::vector<RelatedSite> related_sites;
    std::string site_state;
    std::string site_type;
    std::string site_url;
    Styling styling;
    std::string twitterAccount;
};
extern void from_json(const nlohmann::json& j, Site& r);

}
