cmake_minimum_required(VERSION 3.8)
project(optimizer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-Wall")

find_package(Eigen3 REQUIRED)
include_directories(${EIGEN3_INCLUDE_DIR})

file(GLOB SRC_FILES src/cpp/*.cpp)
file(GLOB HEADERS_FILES src/*.h)
add_library(optimizer ${SRC_FILES})
target_include_directories(optimizer PUBLIC src)

add_executable(optimizer_test main.cpp)
target_link_libraries(optimizer_test optimizer)