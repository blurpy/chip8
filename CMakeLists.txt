cmake_minimum_required(VERSION 3.15)
project(chip8)

set(CMAKE_CXX_STANDARD 17)

find_package(SDL2 REQUIRED)
find_package(Threads REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

add_executable(chip8 src/main.cpp src/Window.cpp src/Window.h src/RomLoader.cpp src/RomLoader.h src/Debugger.cpp src/Debugger.h src/Chip8.cpp src/Chip8.h src/Opcodes.cpp src/Opcodes.h src/Keyboard.cpp src/Keyboard.h src/Timer.cpp src/Timer.h src/Sound.cpp src/Sound.h)
target_link_libraries(chip8 ${SDL2_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})
