# Specify the minimum version for CMake
cmake_minimum_required(VERSION 3.0.2)

set(BINARY_NAME garden)

# Project's name
project(${BINARY_NAME})

# Set the output folder where your program will be created
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)

set(INC_DIRS "include")

include_directories(${INC_DIRS})

file(GLOB BINARY_SOURCES
    "src/*.cpp")

file(GLOB BINARY_HEADERS
    "inc/*.h")

set(BINARY_SOURCE_FILES ${BINARY_SOURCES} ${BINARY_HEADERS})

add_executable(${BINARY_NAME} ${BINARY_SOURCE_FILES})