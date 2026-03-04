cmake_minimum_required(VERSION 3.14)

project(HTMLify-CLI C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_EXPORT_COMPILE_COMMANDS YES)

include_directories(include)

file(GLOB SOURCES "src/*.c")

# Build type detaction
#
# DEV for development
# PROD for production

if(NOT DEFINED BUILD_TYPE)
    set(BUILD_TYPE "DEV" CACHE STRING "Build type: DEV or PROD")
endif()

if(BUILD_TYPE STREQUAL "PROD")
    message(STATUS "Building for Production")
else()
    message(STATUS "Building for Development")
endif()

if(BUILD_TYPE STREQUAL "PROD")
    add_definitions(-DPROD_ENV)
    remove_definitions(-DDEV_ENV)
    set(CMAKE_C_FLAGS "-Wall -Wextra -Wpedantic -O3")
else()
    add_definitions(-DDEV_ENV)
    remove_definitions(-DPROD_ENV)
    set(CMAKE_C_FLAGS "-Wall -Wextra -Wpedantic -O0 -g")
endif()

add_executable(htmlify ${SOURCES})

