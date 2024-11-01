cmake_minimum_required(VERSION 3.10)
project(path_tracer)

set (CMAKE_CXX_STANDARD 17)

add_library(path_tracer.lib src/Vector3D.cpp)

add_executable(path_tracer src/main.cpp)

target_link_libraries(path_tracer path_tracer.lib)