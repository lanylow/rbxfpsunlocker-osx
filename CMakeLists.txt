cmake_minimum_required(VERSION 3.23)
project(rbxfpsunlocker_osx)

set(CMAKE_CXX_STANDARD 17)

file(GLOB_RECURSE SOURCES "${CMAKE_SOURCE_DIR}/src/*.cpp")

include_directories("${CMAKE_SOURCE_DIR}/inc/")

add_executable(rbxfpsunlocker_osx ${SOURCES})
