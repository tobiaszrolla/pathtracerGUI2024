cmake_minimum_required(VERSION 3.10)
project(path_tracer)

set (CMAKE_CXX_STANDARD 17)

add_library(path_tracer.lib src/Vector3D.cpp src/Mesh.cpp src/Triangle.cpp src/PathTracer.cpp src/Material.cpp src/Camera.cpp src/Color.cpp src/TraceRay.cpp)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})


add_executable(path_tracer src/main.cpp)
add_executable(tests src/tests.cpp)

target_link_libraries(path_tracer path_tracer.lib)
target_link_libraries(tests path_tracer.lib gtest gtest_main) 

enable_testing()
add_test(NAME RunAllTests COMMAND tests)