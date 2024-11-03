cmake_minimum_required(VERSION 3.10)
project(Array_Algos)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(SFML_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src/SFML-2.6.1/lib/cmake/SFML")
add_executable(Array_Algos src/array.cpp)
set(SFML_STATIC_LIBRARIES TRUE)
find_package(SFML COMPONENTS system window graphics network audio REQUIRED)
target_include_directories(Array_Algos PUBLIC #TODO Was macht dieser Befehl?
                          "${CMAKE_CURRENT_BINARY_DIR}"
                          "${CMAKE_CURRENT_SOURCE_DIR}/SFML/include/SFML"
                        )
target_link_libraries(Array_Algos sfml-system sfml-window sfml-graphics sfml-network sfml-audio)
