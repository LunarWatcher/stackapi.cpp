#include "stackapi/StackAPI.hpp"
#include "stackapi/data/structs/posts/Answer.hpp"

#include <iostream>

int main() {
    stackapi::StackAPI api (
        {
            .apiKey{API_KEY},
            .site{"stackoverflow"},
            .pageSize = 5,
            .userAgent{"StackAPIDemo/git (+https://github.com/LunarWatcher/stackapi.cpp)"}
        }
    );

    auto res = api.get<stackapi::Answer>("answers", {}, {
        .filter{"!*MjkmyT9x3lPk8ML"},
    });
    std::cout << "Received " << res.items.size() << " answers." << std::endl;
    std::cout << "Samples: " << std::endl;
    for (auto& answer : res.items) {
        std::cout << "Answer to: " << answer.question_id << std::endl;
        std::cout << answer.body_markdown << " - " << answer.owner.display_name << std::endl;
        std::cout << "Comments:" << std::endl;
        if (!answer.comments.size()) {
            std::cout << "None :(" << std::endl;
        } else {
            for (auto& comment : answer.comments) {
                std::cout << "\t" << comment.body_markdown << " - " << comment.owner.display_name << std::endl;
            }
        }

        std::cout << "===========\n\n";

    }
}
