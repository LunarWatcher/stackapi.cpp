#include "stackapi/StackAPI.hpp"
#include "stackapi/data/structs/comments/Comment.hpp"

#include <iostream>

int main() {
    stackapi::StackAPI api (
        {
            .apiKey{API_KEY},
            .site{"stackoverflow"},
            .pageSize = 2,
            .userAgent{"StackAPIDemo/git (+https://github.com/LunarWatcher/stackapi.cpp)"}
        }
    );

    auto res = api.get<stackapi::Comment>("comments", {}, {
        .filter{"!nOedRLmEXx"},
        .pageSize{3},
    });
    std::cout << "Received " << res.items.size() << " comments." << std::endl;
    std::cout << "Samples: " << std::endl;
    for (auto& comment : res.items) {
        std::cout << comment.body_markdown << " - " << comment.owner.display_name << std::endl;
    }
}
