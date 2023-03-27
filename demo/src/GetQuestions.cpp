#include "stackapi/StackAPI.hpp"
#include "stackapi/data/structs/posts/Question.hpp"

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

    auto res = api.get<stackapi::Question>("questions", {}, {
        .filter{"!nOedRLb*BA"},
    });
    std::cout << "Received " << res.items.size() << " questions." << std::endl;
    std::cout << "Samples: " << std::endl;
    for (auto& question : res.items) {
        std::cout << "Question " << question.question_id << ":" << std::endl;
        std::cout << "# " << question.title << std::endl;
        std::cout << "=======\n";

        std::cout << question.body_markdown << std::endl;
        std::cout << "=====\n\n";
    }
}
