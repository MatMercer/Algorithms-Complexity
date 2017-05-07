cmake_minimum_required(VERSION 3.6)
project(algorithms_complexity)

set(CMAKE_CXX_STANDARD 11)

set(SEARCH_ALG_FILES search_algorithms/main.cpp)
add_executable(search_alg ${SEARCH_ALG_FILES})