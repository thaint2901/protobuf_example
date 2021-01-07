# Minimum CMake required
cmake_minimum_required(VERSION 3.14.4)

# Project
project(protobuf-examples)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_subdirectory(protos)

find_package(Protobuf REQUIRED)
include_directories(${CMAKE_BINARY_DIR}/protos)

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} PUBLIC protobuf ${Protobuf_LIBRARIES})
target_include_directories(${PROJECT_NAME} PUBLIC ${Protobuf_INCLUDE_DIRS})