cmake_minimum_required(VERSION 3.15)
project(MINESWEEPER_RAYLIB VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#add_subdirectory(3rdparty/SFML)

file(GLOB_RECURSE SOURCES src/*.cpp)
file(GLOB_RECURSE HEADERS include/*.hpp)

add_executable(MINESWEEPER_RAYLIB 
    src/main.cpp
)

#target_include_directories(MINESWEEPER_RAYLIB PRIVATE ${CMAKE_SOURCE_DIR}/3rdparty/SFML/include)

#target_link_libraries(MINESWEEPER_RAYLIB sfml-graphics sfml-window sfml-system)