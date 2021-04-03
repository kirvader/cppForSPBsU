cmake_minimum_required(VERSION 3.16)
project(lab_07)

set(CMAKE_CXX_STANDARD 17)

include_directories(.)
include_directories(include)
include_directories(src)

add_executable(lab_07 src/main.cpp src/matrix.cpp include/matrix.h)
