cmake_minimum_required(VERSION 3.5)
project(nul_versie)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

include_directories(rtos)
include_directories(hwlib)
include_directories(bmptk)

set(SOURCE_FILES src/main.cpp)

add_executable(nul_versie ${SOURCE_FILES})