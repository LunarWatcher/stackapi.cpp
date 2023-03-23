add_executable(tests 
    src/ABCDTests.cpp
)

Include(FetchContent)

FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG v3.3.0
)

FetchContent_MakeAvailable(Catch2)

target_link_libraries(tests Catch2::Catch2WithMain)

target_link_libraries(tests stackapi)

# vim:ft=cmake
