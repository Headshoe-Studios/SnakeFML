project(SnakeFML)
cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++14")

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

find_package(SFML 2 REQUIRED graphics window system)

include_directories(${SFML_INCLUDE_DIR})

set(HDRS
    Snake.hpp
    Mouse.hpp
    MouseSpawner.hpp
    Button.hpp
    World.hpp
    Score.hpp
    Menu.hpp
)

set(SRCS
    Snake.cpp
    Mouse.cpp
    MouseSpawner.cpp
    Main.cpp
    Button.cpp
    World.cpp
    Score.cpp
    Menu.cpp
    WaterEffect.frag
)

add_executable("${PROJECT_NAME}" ${HDRS} ${SRCS})

target_link_libraries("${PROJECT_NAME}" ${SFML_LIBRARIES})

install(TARGETS "${PROJECT_NAME}" DESTINATION ${CMAKE_INSTALL_PREFIX})
FILE(GLOB images "*.png")
INSTALL(FILES ${images} DESTINATION ${CMAKE_INSTALL_PREFIX})
install(FILES SnakeFML/KBZipaDeeDooDah.ttf DESTINATION ${CMAKE_INSTALL_PREFIX})
install(FILES SnakeFML/WaterEffect.frag DESTINATION ${CMAKE_INSTALL_PREFIX})
