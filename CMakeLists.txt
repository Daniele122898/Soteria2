cmake_minimum_required(VERSION 3.22)
project(Soteria)

set(CMAKE_CXX_STANDARD 20)


add_subdirectory(SoteriaClient)
add_subdirectory(internal/ArgParse)

add_subdirectory(external/fmt)
