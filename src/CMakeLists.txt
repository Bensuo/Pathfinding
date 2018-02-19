# Computer Game AI Assignment

cmake_minimum_required(VERSION 3.2)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

project(Pathfinding)

SET(PATHFINDING_INC
	Graph/DotParser.hpp
	)
	
SET(PATHFINDING_SOURCE
	main.cpp
	Graph/DotParser.cpp
)
SET(PATHFINDING_SRC ${PATHFINDING_INC} ${PATHFINDING_SOURCE})
foreach(_source IN ITEMS ${PATHFINDING_SRC})
    get_filename_component(_source_path "${_source}" PATH)
    string(REPLACE "/" "\\" _source_path_msvc "${_source_path}")
    source_group("${_source_path_msvc}" FILES "${_source}")
endforeach()

include_directories("./")
add_executable(Pathfinding ${PATHFINDING_SRC})