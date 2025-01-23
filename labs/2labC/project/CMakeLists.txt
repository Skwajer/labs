cmake_minimum_required(VERSION 3.28)
project(9 C)

set(CMAKE_C_STANDARD 99)

include_directories(.)

add_executable(project
        ../../../libs/src/types.c
        ../../../libs/src/memory.c
        3/main.c)

