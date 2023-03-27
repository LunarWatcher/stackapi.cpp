#pragma once

#include <nlohmann/json.hpp>
#include "stackapi/data/structs/Types.hpp"

namespace stackapi {

struct BadgeCount {
    API_INT bronze;
    API_INT silver;
    API_INT gold;
};

extern void from_json(const nlohmann::json &j, BadgeCount& count);

}
