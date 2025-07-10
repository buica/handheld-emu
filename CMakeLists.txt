cmake_minimum_required(VERSION 3.5)
project(handheld-emu)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

enable_testing()

add_executable(handheld-emu main.cpp)
