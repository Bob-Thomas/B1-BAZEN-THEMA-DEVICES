cmake_minimum_required(VERSION 3.5)
project(nul_versie)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

include_directories("../libs/hwlib")
include_directories("../libs/bmptk")
include_directories("../libs/rtos")

set(SOURCE_FILES src/main.cpp)

add_executable(nul_versie ${SOURCE_FILES})