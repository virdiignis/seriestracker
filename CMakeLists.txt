cmake_minimum_required(VERSION 3.12)
project(seriestracker)

set(CMAKE_CXX_STANDARD 17)
find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

add_executable(seriestracker main.cpp Pool.cpp Pool.hpp Database.hpp Piece.cpp Piece.hpp Series.cpp Series.hpp Interface.cpp Interface.hpp Film.cpp Film.hpp Ppv.cpp Ppv.hpp constants.hpp)

target_link_libraries(seriestracker ${CURSES_LIBRARIES})
target_link_libraries(seriestracker stdc++fs)