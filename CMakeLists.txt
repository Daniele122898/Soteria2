cmake_minimum_required(VERSION 3.16.3)

project(Soteria)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(SoteriaClient)
add_subdirectory(SoteriaServer)
add_subdirectory(internal/ArgParse)

add_subdirectory(external/fmt)
add_subdirectory(external/crow)
add_subdirectory(external/cpr)
