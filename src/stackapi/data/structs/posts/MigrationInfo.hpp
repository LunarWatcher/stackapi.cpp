#pragma once

#include <nlohmann/json.hpp>
#include <string>

#include "stackapi/data/structs/network/Site.hpp"
#include "stackapi/data/structs/Types.hpp"

namespace stackapi {

struct MigrationInfo {
    API_DATE on_date;
    Site origin;
    API_INT question_id;
};
extern void from_json(const nlohmann::json &j, MigrationInfo &r);

}
