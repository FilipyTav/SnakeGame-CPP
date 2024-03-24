cmake_minimum_required(VERSION 3.7...3.28)

if(${CMAKE_VERSION} VERSION_LESS 3.12)
    cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
endif()

project(
        "SnakeGame"
        VERSION 1.0
        DESCRIPTION "Game made with raylib"
        LANGUAGES CXX
       )

set (CMAKE_CXX_STANDARD 20)

set(SRC_DIR "src")
set(BUILD_DIR "build")
set(BIN_DIR "bin")
set(INC_DIRS
    "include"
    "~/Documents/Coding/GameDev/Raylib/cpp/include/"
    )

set(CMAKE_BUILD_TYPE "Debug")
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/${BIN_DIR}")

file(GLOB_RECURSE SOURCES RELATIVE ${CMAKE_SOURCE_DIR} "${SRC_DIR}/*.cpp")
add_executable(${PROJECT_NAME} ${SOURCES})

# -------------------- System libs -------------------->

## Raylib

set(LIBS "raylib")
target_link_libraries(${PROJECT_NAME} PRIVATE "${LIBS}")

# <-------------------- System libs --------------------

target_include_directories(${PROJECT_NAME} PRIVATE "${INC_DIRS}")

# Set the asset path macro to the absolute path on the dev machine
target_compile_definitions(${PROJECT_NAME} PUBLIC ASSETS_PATH="${CMAKE_CURRENT_SOURCE_DIR}/assets/")

# Set the asset path macro in release mode to a relative path that assumes the assets folder is in the same directory as the game executable
# target_compile_definitions(${PROJECT_NAME} PUBLIC ASSETS_PATH="./assets")
