cmake_minimum_required(VERSION 3.10)

# Project name
project(ZombieDice VERSION 1.0)

# C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# include directories
include_directories(${PROJECT_SOURCE_DIR}/include)

# source files
file(GLOB SOURCES "src/*.cpp")

# executable
add_executable(zombie-dice ${SOURCES})