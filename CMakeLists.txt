cmake_minimum_required(VERSION 3.12)
project(seriestracker)

set(CMAKE_CXX_STANDARD 14)

add_executable(seriestracker main.cpp Pool.cpp Pool.hpp Database.cpp Database.hpp Piece.cpp Piece.hpp Series.cpp Series.hpp)