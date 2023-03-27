#pragma once

#include "nlohmann/json.hpp"

#include <string>
#include "stackapi/data/structs/Types.hpp"

namespace stackapi {

struct OriginalQuestion {
    API_INT accepted_answer_id;
    API_INT answer_count;
    API_INT question_id;
    std::string title;
};

extern void from_json(const nlohmann::json& j, OriginalQuestion& r);

}
