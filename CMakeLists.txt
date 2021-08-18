cmake_minimum_required(VERSION 3.0)
project(raytracer)

set(CMAKE_CXX_STANDARD 17)

add_executable(raytracer main.cpp datatypes.cpp functions.cpp)
add_executable(raytracer_tests tests.cpp datatypes.cpp functions.cpp)
