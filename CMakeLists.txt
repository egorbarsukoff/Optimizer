cmake_minimum_required(VERSION 3.8)
project(optimizer)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES main.cpp src/Function.h src/Optimizer.h src/Criteria.h src/cpp/Vector.cpp src/Gradient.h src/cpp/BoxDomain.cpp src/cpp/Random.cpp src/cpp/RandomSearch.cpp src/cpp/Criteria.cpp)
add_executable(optimizer ${SOURCE_FILES})