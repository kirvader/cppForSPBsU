cmake_minimum_required(VERSION 3.16)
project(lab_08)

set(CMAKE_CXX_STANDARD 17)

include_directories(".")
include_directories("include")
include_directories("src")

add_executable(lab_08 src/shared_ptr.cpp include/shared_ptr.hpp src/matrix.cpp include/matrix.hpp src/main.cpp)