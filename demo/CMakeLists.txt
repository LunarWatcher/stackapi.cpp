add_compile_definitions("API_KEY=\"k60dxEVfvM5wJ2foUbE7eQ((\"")

add_executable(get-comments src/GetComments.cpp)
target_link_libraries(get-comments stackapi)

add_executable(get-questions src/GetQuestions.cpp)
target_link_libraries(get-questions stackapi)

add_executable(get-answers src/GetAnswers.cpp)
target_link_libraries(get-answers stackapi)
