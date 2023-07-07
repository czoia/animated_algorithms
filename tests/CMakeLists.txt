cmake_minimum_required(VERSION 3.5)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

find_package(Catch2 3 REQUIRED)
add_executable(tests binarytree.cpp)
target_link_libraries(tests PRIVATE Catch2::Catch2WithMain)
