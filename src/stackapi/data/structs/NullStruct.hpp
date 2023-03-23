#pragma once

#include "nlohmann/json_fwd.hpp"

namespace stackapi {

struct NullStruct {};

extern void from_json(const nlohmann::json& j, NullStruct& r);

}
