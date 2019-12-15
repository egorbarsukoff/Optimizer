cmake_minimum_required(VERSION 3.8)
project(optimizer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-Wall")

find_package(Eigen3 REQUIRED)
include_directories(${EIGEN3_INCLUDE_DIR})

add_subdirectory(optim)

add_executable(optimizer_test main.cpp optim/cpp/Functions.cpp)
target_link_libraries(optimizer_test optimizer)