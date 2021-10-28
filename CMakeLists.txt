cmake_minimum_required(VERSION 3.20)
project(linked_list_test_module)

set(CMAKE_CXX_STANDARD 14)

add_executable(linked_list_test_module test.c macro.h linked_list_api.h linked_list_api.c data_structure.h time_calculating.h time_calculating.c data_structure.c)