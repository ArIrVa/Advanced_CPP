cmake_minimum_required(VERSION 3.5)
project(test)
find_package(Catch2 3 REQUIRED)
add_executable(${PROJECT_NAME} test_list.cpp )
target_link_libraries(${PROJECT_NAME} PRIVATE Catch2::Catch2WithMain)

