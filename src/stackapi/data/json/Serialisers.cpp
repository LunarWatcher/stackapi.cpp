#include <nlohmann/json.hpp>

#include "stackapi/data/structs/NullStruct.hpp"

namespace stackapi {

#pragma optimize("", off)
void from_json(const nlohmann::json& j, NullStruct& r) {}
#pragma optimize("", on)

}
