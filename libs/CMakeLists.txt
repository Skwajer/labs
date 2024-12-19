cmake_minimum_required(VERSION 3.28)
project(libs C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(libs src/types.c
        src/memory.c
        types.h)
