project(SnakeFML)
cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

find_package(SFML 2 REQUIRED graphics window system)
find_package(Threads)

include_directories(${SFML_INCLUDE_DIR})

set(HDRS
    SnakeFML/Snake.hpp
    SnakeFML/Mouse.hpp
    SnakeFML/MouseSpawner.hpp
)

set(SRCS
    SnakeFML/Snake.cpp
    SnakeFML/Mouse.cpp
    SnakeFML/MouseSpawner.cpp
    SnakeFML/Main.cpp
)

add_executable("${PROJECT_NAME}-exec" ${HDRS} ${SRCS})

target_link_libraries("${PROJECT_NAME}-exec" ${SFML_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})
