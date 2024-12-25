cmake_minimum_required(VERSION 3.28)
project(9 C)

set(CMAKE_C_STANDARD 99)

include_directories(.)

add_executable(project
        11/tokenize_realization.c
        11/tokenize_realization.h
        ../../../libs/src/types.c
        ../../../libs/src/memory.c
        ../../../libs/errors.h
        11/main.c
)

