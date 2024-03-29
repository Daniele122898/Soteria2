cmake_minimum_required(VERSION 3.16.3)
project(ArgParse)

set(CMAKE_CXX_STANDARD 20)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS "src/*.cpp" "src/*.h")
add_library(${PROJECT_NAME} ${SOURCES})

if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /W4 /WX /wd4201)
else()
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Werror -Wno-unused-variable -Wno-unused-function -fdiagnostics-show-template-tree)
endif()

target_include_directories(${PROJECT_NAME}
        PUBLIC
            $<INSTALL_INTERFACE:include>
            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
            fmt
)

target_link_libraries(${PROJECT_NAME}
        PUBLIC
            fmt
)