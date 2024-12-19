cmake_minimum_required(VERSION 3.28)
project(9 C)

set(CMAKE_C_STANDARD 99)

include_directories(.)

add_executable(project
        10/my_scanf.c
        10/my_scanf.h
        ../../../libs/src/types.c
        ../../../libs/src/memory.c
        ../../../libs/errors.h
        10/main.c
)

