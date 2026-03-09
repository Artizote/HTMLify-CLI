cmake_minimum_required(VERSION 3.14)

project(HTMLify-CLI C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_EXPORT_COMPILE_COMMANDS YES)

include_directories(include)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS "src/*.c")

add_executable(htmlify ${SOURCES})

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


# External dependincies
include(FetchContent)

# Curl Lib

find_package(CURL REQUIRED)
include_directories(${CURL_INCLUDE_DIR})
target_link_libraries(htmlify PRIVATE CURL::libcurl)

# cJSON

FetchContent_Declare(
    cjson
    GIT_REPOSITORY https://github.com/DaveGamble/cJSON.git
    GIT_TAG v1.7.19
)

set(ENABLE_CJSON_TEST OFF CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(cjson)

target_include_directories(htmlify PRIVATE ${cjson_SOURCE_DIR})

target_link_libraries(htmlify PRIVATE cjson)

