#pragma once

#include <string>
#include <nlohmann/json.hpp>

namespace stackapi {

struct Styling {
    std::string link_color;
    std::string tag_background_color;
    std::string tag_foreground_color;
};

extern void from_json(const nlohmann::json& j, Styling& r);

}
