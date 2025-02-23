cmake_minimum_required(VERSION 3.28)
project(1 CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-subsystem,console")

include_directories(.)

add_executable(1labcpp 1v2.cpp)