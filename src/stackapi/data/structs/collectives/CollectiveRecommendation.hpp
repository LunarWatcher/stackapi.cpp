#pragma once

#include "Collective.hpp"

#include "stackapi/data/structs/Types.hpp"

namespace stackapi {

struct CollectiveRecommendation {
    Collective collective;
    API_DATE creation_date;
};

extern void from_json(const nlohmann::json& j, CollectiveRecommendation& r);

}
