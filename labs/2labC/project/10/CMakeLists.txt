cmake_minimum_required(VERSION 3.28)
project(10 C)

set(CMAKE_C_STANDARD 99)

include_directories(.)

add_executable(10
        main.c
        my_scanf.h
        my_scanf.c
        ../../../../libs/types.c
        )
