cmake_minimum_required(VERSION 3.0)

set(NAME "Rollercoaster")

file(GLOB SOURCES src/*.cpp)
file(GLOB HEADERS include/*.h include/*.hpp)

project(${NAME})
add_executable(${NAME} main.cpp)

target_link_libraries(${NAME} sfml-graphics sfml-system sfml-window)
