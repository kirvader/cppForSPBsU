cmake_minimum_required(VERSION 3.16)
project(lab_06)

set(CMAKE_CXX_STANDARD 17)

include_directories(.)
include_directories(include)
include_directories(src)

add_executable(lab_06 src/main.cpp src/my_vector.cpp include/my_vector.h)