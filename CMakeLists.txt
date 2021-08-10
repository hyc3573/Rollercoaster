cmake_minimum_required(VERSION 3.0)

set(NAME "Rollercoaster")

add_compile_options(-Wall -Wextra -Wpedantic -pedantic -ggdb3 -I../include)

file(GLOB SOURCES src/*.cpp)
file(GLOB HEADERS include/*.h include/*.hpp)

project(${NAME})
add_executable(${NAME} ${SOURCES} ${HEADERS})

target_link_libraries(${NAME} sfml-graphics sfml-system sfml-window)
