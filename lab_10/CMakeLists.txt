cmake_minimum_required(VERSION 3.16)
project(lab_10)

set(CMAKE_CXX_STANDARD 17)

include_directories(.)
include_directories(src)
include_directories(include)

add_executable(lab_10 src/main.cpp src/employees.cpp include/employees.h)