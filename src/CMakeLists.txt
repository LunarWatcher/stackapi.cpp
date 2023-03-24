add_library(stackapi
    stackapi/StackAPI.cpp

    stackapi/data/json/Deserialisers.cpp
)

target_include_directories(stackapi PUBLIC ./)
target_include_directories(stackapi PUBLIC ${CONAN_INCLUDE_DIRS})

target_link_libraries(stackapi PUBLIC ${CONAN_LIBS})

# vim:ft=cmake
