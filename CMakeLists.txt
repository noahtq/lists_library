cmake_minimum_required(VERSION 3.28)
project(practice_03_linked_list)

set(CMAKE_CXX_STANDARD 17)

add_executable(practice_03_linked_list main.cpp
        lists.cpp
        lists.h
        Google_tests/test_lists.cpp)

add_subdirectory(Google_tests)
