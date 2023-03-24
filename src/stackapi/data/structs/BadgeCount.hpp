#pragma once

#include <nlohmann/json.hpp>

namespace stackapi {

struct BadgeCount {
    int bronze;
    int silver;
    int gold;
};

extern void from_json(const nlohmann::json &j, BadgeCount& count);

}
