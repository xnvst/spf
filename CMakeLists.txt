cmake_minimum_required(VERSION 2.8.3)
project(single_pixel_filter CXX)

set(LINKED_LIBRARIES)

add_library(lib_spf SHARED single_pixel_filter.cpp)

add_executable(spf_tester spf_tester.cpp)
target_link_libraries(spf_tester lib_spf)
