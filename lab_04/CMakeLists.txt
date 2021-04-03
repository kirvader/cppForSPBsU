cmake_minimum_required(VERSION 3.17)
project(lab_04 C)

set(CMAKE_C_STANDARD 99)

include_directories(.)
include_directories(include)
include_directories(src)

add_executable(lab_04
        include/clist.h
        src/main.c
        src/clist.c
        Makefile)