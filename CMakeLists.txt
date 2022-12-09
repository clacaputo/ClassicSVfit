# https://stackoverflow.com/questions/17511496/how-to-create-a-shared-library-with-cmake
cmake_minimum_required(VERSION 3.10)
# set the project name
project(SVfit VERSION 1.0 DESCRIPTION "ClassicSVfit-FastMTT shared lib")
# Sets up global settings
# include("${ROOT_USE_FILE}")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 ")
add_subdirectory(src)
add_subdirectory(bin)