cmake_minimum_required(VERSION 3.8)
project(optimizer)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES main.cpp src/Function.h src/Optimizer.h src/Criterion.h src/Vector.h src/BoxDomain.h src/Gradient.h src/RandomSearch.h src/CommonRandom.h)
add_executable(optimizer ${SOURCE_FILES})