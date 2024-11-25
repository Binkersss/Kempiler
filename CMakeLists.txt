cmake_minimum_required(VERSION 3.10)
project(kempiler)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add executable
add_executable(kempiler
        src/main.cpp
)

# Include directories
target_include_directories(kempiler PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)