cmake_minimum_required(VERSION 3.10)
project(stackapi.cpp)

if (CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    message (STATUS "stackapi.cpp: Running standalone")
    set (ENABLE_DEMOS ON)
else()
    message (STATUS "stackapi.cpp: Running as a submodule; disabling demos.")
    set (ENABLE_DEMOS OFF)
endif()

set (CMAKE_CXX_STANDARD 20)

include(FetchContent)
FetchContent_Declare(fmt GIT_REPOSITORY https://github.com/fmtlib/fmt.git
    GIT_TAG 9.1.0)
FetchContent_MakeAvailable(fmt)

set(SPDLOG_FMT_EXTERNAL ON)
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

if (ENABLE_DEMOS)
    add_subdirectory(demo)
endif()

# vim:ft=cmake
