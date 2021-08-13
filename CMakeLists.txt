cmake_minimum_required(VERSION 3.0)

set(NAME "Rollercoaster")
set(CMAKE_CXX_STANDARD 14)

add_compile_options(-Wall -Wextra -Wpedantic -pedantic -ggdb3 -I../include)

file(GLOB SOURCES src/*.cpp)
file(GLOB HEADERS include/*.h include/*.hpp)

project(${NAME})
add_executable(${NAME} ${SOURCES} ${HEADERS})

target_include_directories(Rollercoaster PRIVATE /usr/include/python3.8)

if(CMAKE_EXE_LINKER_FLAGS STREQUAL "-static")
	target_compile_definitions(Rollercoaster PUBLIC SFML_STATIC)
	target_link_libraries(Rollercoaster sfml-graphics-s)
	target_link_libraries(Rollercoaster sfml-window-s)
	target_link_libraries(Rollercoaster sfml-system-s)
	target_link_libraries(Rollercoaster opengl32)
	target_link_libraries(Rollercoaster winmm)
	target_link_libraries(Rollercoaster gdi32)
else()
	target_link_libraries(Rollercoaster "sfml-graphics")
	target_link_libraries(Rollercoaster "sfml-window")
	target_link_libraries(Rollercoaster "sfml-system")
	target_link_libraries(Rollercoaster "tgui")
endif()
