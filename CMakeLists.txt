cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 11)

find_package(OpenMP)
if (OPENMP_FOUND)
	set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
	set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
	set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
endif()

add_executable(
demo ./forcelayout/src/layout.cc ./nangraph/src/graph.cc ./quadtree/src/quadtree.cc ./demo.cpp
)

target_include_directories(
demo PRIVATE
./forcelayout/include ./nangraph/include ./quadtree/include ./random/include
)

add_executable(
gen ./gener.cpp
)
