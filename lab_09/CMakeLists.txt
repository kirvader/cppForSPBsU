cmake_minimum_required(VERSION 3.16)
project(lab_09)

set(CMAKE_CXX_STANDARD 14)

include_directories(src)
include_directories(include)
include_directories(.)

add_executable(lab_09 src/Circle.cpp include/Circle.hpp src/Rectangle.cpp include/Rectangle.hpp src/Scheme.cpp include/Scheme.hpp src/Figure.cpp include/Figure.hpp src/main.cpp)