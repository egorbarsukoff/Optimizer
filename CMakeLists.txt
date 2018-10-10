cmake_minimum_required(VERSION 3.8)
project(optimizer)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES main.cpp
        src/cpp/Vector.cpp src/cpp/BoxDomain.cpp src/cpp/Random.cpp src/cpp/RandomSearch.cpp
        src/cpp/Criterion.cpp src/cpp/Gradient.cpp src/cpp/Optimizer.cpp src/cpp/Function.cpp)
add_executable(optimizer ${SOURCE_FILES})