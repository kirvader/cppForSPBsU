cmake_minimum_required(VERSION 3.17)
project(lab_05 C)

set(CMAKE_C_STANDARD 99)

include_directories(.)
include_directories(include)
include_directories(src)

add_executable(lab_05
        include/clist.h
        include/point_list.h
        src/main.c
        src/point_list.c
        src/clist.c
)