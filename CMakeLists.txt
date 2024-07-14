cmake_minimum_required(VERSION 3.24)

project(boiderinos-proj LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR})

# Uncomment for static libraries
#set(SFML_STATIC_LIBRARIES TRUE)
find_package(SFML 2.6.1 COMPONENTS graphics window system REQUIRED)

add_executable(boids
    src/main.cpp
    src/Game.cpp
    src/GameUtil.cpp
)
target_include_directories(boids PRIVATE 
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/external/imgui-sfml
)
#target_link_libraries(boids sfml-graphics)

set(IMGUI_DIR ${CMAKE_SOURCE_DIR}/external/imgui)
set(IMGUI_SFML_FIND_SFML OFF)
set(IMGUI_SFML_IMGUI_DEMO ON)
add_subdirectory(external/imgui-sfml)
target_link_libraries(boids PRIVATE ImGui-SFML::ImGui-SFML)

# Copy necessary files into build dir
configure_file(font/GohuFont14NerdFont-Regular.ttf 
    font/GohuFont14NerdFont-Regular.ttf 
    COPYONLY
)