project(SnakeFML)
cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++14")

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

find_package(SFML 2 REQUIRED graphics window system)

include_directories(${SFML_INCLUDE_DIR})

set(HDRS
    SnakeFML/Snake.hpp
    SnakeFML/Mouse.hpp
    SnakeFML/MouseSpawner.hpp
    SnakeFML/Button.h
    SnakeFML/World.h
)

set(SRCS
    SnakeFML/Snake.cpp
    SnakeFML/Mouse.cpp
    SnakeFML/MouseSpawner.cpp
    SnakeFML/Main.cpp
    SnakeFML/Button.cpp
    SnakeFML/World.cpp
)

add_executable("${PROJECT_NAME}-exec" ${HDRS} ${SRCS})

target_link_libraries("${PROJECT_NAME}-exec" ${SFML_LIBRARIES})

install(TARGETS "${PROJECT_NAME}-exec" DESTINATION ${CMAKE_INSTALL_PREFIX})
install(FILES SnakeFML/Mouse.png DESTINATION ${CMAKE_INSTALL_PREFIX})
install(FILES SnakeFML/Grass.png DESTINATION ${CMAKE_INSTALL_PREFIX})
install(FILES SnakeFML/SnakeHead.png DESTINATION ${CMAKE_INSTALL_PREFIX})
install(FILES SnakeFML/LiberationSans-Regular.ttf DESTINATION ${CMAKE_INSTALL_PREFIX})
