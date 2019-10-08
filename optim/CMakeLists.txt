file(GLOB SRC_FILES cpp/*.cpp)
add_library(optimizer ${SRC_FILES})
target_include_directories(optimizer PUBLIC include)