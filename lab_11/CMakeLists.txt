cmake_minimum_required(VERSION 3.16.3)
project(lab_11)

set(CMAKE_CXX_STANDARD 17)

include_directories(.)
include_directories(src)
include_directories(include)

add_executable(lab_11 src/main.cpp include/my_vector.h include/my_vector_impl.h)