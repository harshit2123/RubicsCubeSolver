cmake_minimum_required(VERSION 3.30)
project(RubicsCubeSolver)

set(CMAKE_CXX_STANDARD 26)

add_executable(RubicsCubeSolver main.cpp
        GenericRubicsCube.cpp
        GenericRubicsCube.h
        RubiksCube3dArray.h
        RubiksCube1DArray.h)
