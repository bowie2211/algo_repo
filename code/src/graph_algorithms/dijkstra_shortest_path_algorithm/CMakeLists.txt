cmake_minimum_required(VERSION 3.5.0)
project(dijkstra_shortest_algorithm VERSION 0.1.0 LANGUAGES C CXX)

add_executable(dijkstra_shortest_algorithm dijkstra.cpp)

include(CTest)
enable_testing()

