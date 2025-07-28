cmake_minimum_required(VERSION 3.26)

project(MinesweeperTerminalCpp VERSION 1.0 LANGUAGES CXX)

# Set C++23 standard and no compiler extensions
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_SCAN_FOR_MODULES ON)

# List all sources explicitly
set(SOURCES
    src/main.cpp
    include/Game.cppm
    src/Game.cpp
)

add_executable(MinesweeperTerminalCpp ${SOURCES})

# Include directory for module interface headers
target_include_directories(MinesweeperTerminalCpp PRIVATE include)

# Mark the module interface file so CMake treats it correctly
set_source_files_properties(include/Game.cppm PROPERTIES
    CXX_MODULE_INTERFACE_HEADER_ONLY ON
)

# Enable warnings and optimizations for MSVC
if(MSVC)
    target_compile_options(MinesweeperTerminalCpp PRIVATE /W4 /O2)
endif()