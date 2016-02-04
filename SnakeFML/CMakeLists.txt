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
    SnakeFML/Button.hpp
    SnakeFML/World.hpp
    SnakeFML/Score.hpp
    SnakeFML/Menu.hpp
)

set(SRCS
    SnakeFML/Snake.cpp
    SnakeFML/Mouse.cpp
    SnakeFML/MouseSpawner.cpp
    SnakeFML/Main.cpp
    SnakeFML/Button.cpp
    SnakeFML/World.cpp
    SnakeFML/Score.cpp
    SnakeFML/Menu.cpp
    SnakeFML/WaterEffect.frag
)

add_executable("${PROJECT_NAME}-exec" ${HDRS} ${SRCS})

target_link_libraries("${PROJECT_NAME}-exec" ${SFML_LIBRARIES})

install(TARGETS "${PROJECT_NAME}-exec" DESTINATION ${CMAKE_INSTALL_PREFIX})
FILE(GLOB images "SnakeFML/*.png")
INSTALL(FILES ${images} DESTINATION ${CMAKE_INSTALL_PREFIX})
install(FILES SnakeFML/KBZipaDeeDooDah.ttf DESTINATION ${CMAKE_INSTALL_PREFIX})
install(FILES SnakeFML/WaterEffect.frag DESTINATION ${CMAKE_INSTALL_PREFIX})
