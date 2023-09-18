cmake_minimum_required(VERSION 3.23)
project(dom3)

set(CMAKE_CXX_STANDARD 14)

add_executable(dom3 main.cpp Heap.cpp Heap.h PQueue.cpp PQueue.h)
