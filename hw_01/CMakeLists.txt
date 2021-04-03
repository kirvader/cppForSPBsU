cmake_minimum_required(VERSION 3.17)
project(hw_01 C)

set(CMAKE_C_STANDARD 99)

include_directories(.)
include_directories(include)
include_directories(src)

add_executable(hw_01
        src/main.c
        include/bmp.h
        src/bmp.c)