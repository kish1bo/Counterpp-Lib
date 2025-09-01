cmake_minimum_required(VERSION 3.10)
project(CounterPP LANGUAGES CXX)

# Using C++20 standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Adding static lib from src
add_library(counterpp STATIC
    src/calc.cpp
)

# Include directory for the library
target_include_directories(counterpp PUBLIC include)

# Test executable
add_executable(main test/main.cpp)

# Linking the library to the test executable
target_link_libraries(main PRIVATE counterpp)
