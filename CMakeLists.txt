cmake_minimum_required(VERSION 3.17)
project(fiboHeap)

set(CMAKE_CXX_STANDARD 14)

add_executable(fiboHeap main.cpp FibonacciHeap.h Node.h)