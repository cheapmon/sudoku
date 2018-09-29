cmake_minimum_required(VERSION 3.12)
project(sudoku)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -O4 -g")

find_package(Threads)

add_executable(sudoku
        sudoku.cpp
        board.h
        board.cpp
        util.h
        util.cpp
        solver/greedy_solver.h
        solver/greedy_solver.cpp
        solver/recursive_solver.h
        solver/recursive_solver.cpp
        solver/solver.h)

target_link_libraries(sudoku Threads::Threads)