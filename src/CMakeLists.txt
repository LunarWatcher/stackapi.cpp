add_library(stackapi
    stackapi/StackAPI.cpp

    stackapi/data/json/Deserialisers.cpp
)

target_include_directories(stackapi PUBLIC ./)

target_link_libraries(stackapi PUBLIC cpr::cpr nlohmann_json::nlohmann_json spdlog::spdlog)

# vim:ft=cmake
