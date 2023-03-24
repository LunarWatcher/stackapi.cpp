cmake_minimum_required(VERSION 3.10)
project(stackapi.cpp)

set (CMAKE_CXX_STANDARD 20)

include(FetchContent)
FetchContent_Declare(cpr GIT_REPOSITORY https://github.com/libcpr/cpr.git
                         GIT_TAG 1.10.0)
FetchContent_MakeAvailable(cpr)

FetchContent_Declare(nlohmann GIT_REPOSITORY https://github.com/nlohmann/json
    GIT_TAG v3.11.2)
FetchContent_MakeAvailable(nlohmann)

FetchContent_Declare(spdlog GIT_REPOSITORY https://github.com/gabime/spdlog
    GIT_TAG v1.11.0)
FetchContent_MakeAvailable(spdlog)


add_subdirectory(src)
#add_subdirectory(tests)

#add_custom_target(test
    #COMMAND tests
    #DEPENDS tests
    #COMMENT "Test stackapi.cpp")
# vim:ft=cmake
