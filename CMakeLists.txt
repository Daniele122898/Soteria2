cmake_minimum_required(VERSION 3.16.3)

project(Soteria)

set(CMAKE_CXX_STANDARD 20)

if(WIN32) # Install dlls in the same directory as the executable on Windows
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
endif()

add_subdirectory(SoteriaClient)
add_subdirectory(SoteriaServer)
add_subdirectory(internal/ArgParse)
add_subdirectory(internal/Util)

add_subdirectory(external/fmt)
add_subdirectory(external/crow)
add_subdirectory(external/json)
add_subdirectory(external/sqlite)

if(WIN32)
    SET(CPR_FORCE_USE_SYSTEM_CURL ON)
else()
    SET(CPR_FORCE_USE_SYSTEM_CURL OFF)
endif()


add_subdirectory(external/cpr)
