cmake_minimum_required(VERSION 3.30)
project(RubicsCubeSolver)

set(CMAKE_CXX_STANDARD 26)

add_executable(RubicsCubeSolver main.cpp
        Modal/GenericrubiksCube.h
        Modal/RubiksCube3dArray.h
        Modal/RubiksCube1DArray.cpp
        Solver/DFSSolver.h
        Solver/BFSSOLVER.h
        Solver/IDDFSSolver.h
        Solver/IDAstarSolver.h
        Modal/GenericRubiksCube.cpp
        Modal/GenericRubiksCube.cpp)
