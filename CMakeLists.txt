cmake_minimum_required(VERSION 3.28)

project(Minesweeper LANGUAGES CXX)

# Require C++23 and enable module support
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPERIMENTAL_CXX_MODULE_CMAKE_API YES)

# Add the Game module library with interface and implementation
add_library(Game
    src/Game.cpp
    include/Game.ixx
    include/TextColors.ixx
)

# Mark the module interface file explicitly
target_sources(Game
    PRIVATE
        FILE_SET cxx_modules TYPE CXX_MODULES FILES
        include/Game.ixx
        include/TextColors.ixx
)

# Add executable
add_executable(Minesweeper
    src/main.cpp
    src/Game.cpp
)

# Link the Game module to the executable
target_link_libraries(Minesweeper PRIVATE Game)

# Include the module interface headers
target_include_directories(Game PRIVATE include)
target_include_directories(Minesweeper PRIVATE include)