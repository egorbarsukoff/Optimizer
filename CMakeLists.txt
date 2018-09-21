cmake_minimum_required(VERSION 3.8)
project(optimizer)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp src/Function.cpp src/Function.h src/Optimizer.cpp src/Optimizer.h)
add_executable(optimizer ${SOURCE_FILES})