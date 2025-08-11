cmake_minimum_required(VERSION 3.15)
project(handheld-emu LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(EMU_SOURCES
    # src/system.cpp
    src/cpu.cpp
    # src/memory.cpp
    # src/cart.cpp
    #src/ppu.cpp
    # src/io_registers.cpp
    #src/timer.cpp
)


add_library(handheld-core STATIC ${EMU_SOURCES})
target_include_directories(handheld-core PUBLIC ${CMAKE_SOURCE_DIR}/include)

add_executable(handheld-emu src/main.cpp)
target_link_libraries(handheld-emu PRIVATE handheld-core)

include(CTest)

include(FetchContent)
FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG        v3.8.1
)
FetchContent_MakeAvailable(Catch2)

add_executable(
    tests
    tests/cpu_tests.cpp
)
target_link_libraries(tests PRIVATE handheld-core Catch2::Catch2WithMain)

list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)
include(Catch)
catch_discover_tests(tests)
