cmake_minimum_required(VERSION 3.3)
project(LabaKiller)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp Tree.h RecursiveDescent.h PrintTrees.h Derivatives.h TexMaking.h)
add_executable(LabaKiller ${SOURCE_FILES})