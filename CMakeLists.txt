cmake_minimum_required(VERSION 3.15)
project(chip8)

set(CMAKE_CXX_STANDARD 17)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

add_executable(chip8 src/main.cpp src/Window.cpp src/Window.h)
target_link_libraries(chip8 ${SDL2_LIBRARIES})
