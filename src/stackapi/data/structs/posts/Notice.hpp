#pragma once

#include <string>
#include <nlohmann/json.hpp>

#include "stackapi/data/structs/Types.hpp"

namespace stackapi {

struct Notice {
    std::string body;
    API_DATE creation_date;
    API_INT owner_user_id;
};

extern void from_json(const nlohmann::json& j, Notice& r);

}
