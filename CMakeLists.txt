cmake_minimum_required(VERSION 3.10)
project(example)

set(CMAKE_CXX_STANDARD 11)

add_executable(example
    Debug/src/example.d
    Debug/src/example.o
    Debug/src/lecture_graph.d
    Debug/src/lecture_graph.o
    Debug/src/subdir.mk
    Debug/example
    Debug/makefile
    Debug/objects.mk
    Debug/sources.mk
    src/example.cpp
    src/lecture_graph.cpp
    README.md)
