cmake_minimum_required(VERSION 3.16.3)

project(SoteriaClient)

set(CMAKE_CXX_STANDARD 20)

# Get recursively all .cpp and .hpp files in src subdir
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS "src/*.cpp" "src/*.h")

add_executable(${PROJECT_NAME} ${SOURCES})
#add_subdirectory(../internal/ArgParse)

find_package(OpenSSL REQUIRED)
SET(CPR_FORCE_USE_SYSTEM_CURL)

if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /W4 /WX /wd4201)
else()
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Werror -Wno-unused-function -Wno-unused-parameter -Wno-unused-variable -fdiagnostics-show-template-tree)
endif()

target_include_directories(${PROJECT_NAME}
        PUBLIC
            ArgParse
            cpr
            fmt
            Util
            nlohmann_json
)

target_link_libraries(${PROJECT_NAME}
        PUBLIC
            ArgParse
            cpr
            fmt
            Util
            nlohmann_json
        PRIVATE
            OpenSSL::Crypto
            OpenSSL::SSL
)

