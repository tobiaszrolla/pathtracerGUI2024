cmake_minimum_required(VERSION 3.10)
project(path_tracer LANGUAGES CXX CUDA)

set(CMAKE_CXX_STANDARD 17)

set(CUDA_TOOLKIT_ROOT_DIR "/mnt/c/Program Files/NVIDIA GPU Computing Toolkit/CUDA/v12.0")
set(CMAKE_CUDA_ARCHITECTURES 80)

enable_language(CUDA)

add_library(path_tracer.lib STATIC src/Vector3D.cu src/Mesh.cpp src/Triangle.cu src/PathTracer.cu src/Material.cu src/Camera.cu src/Color.cu src/TraceRay.cu src/kernel.cu)
target_include_directories(path_tracer.lib PRIVATE include)

set_target_properties( path_tracer.lib
                       PROPERTIES CUDA_SEPARABLE_COMPILATION ON)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(path_tracer src/main.cu)
add_executable(tests src/tests.cpp)

set_target_properties( path_tracer
                       PROPERTIES CUDA_SEPARABLE_COMPILATION ON)

target_link_libraries(path_tracer PRIVATE path_tracer.lib)
target_link_libraries(tests path_tracer.lib gtest gtest_main) 

enable_testing()
add_test(NAME RunAllTests COMMAND tests)