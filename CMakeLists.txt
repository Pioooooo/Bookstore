cmake_minimum_required(VERSION 3.10.2)
project(bookstore)
set(CMAKE_CXX_STANDARD 14)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}   -g")
include_directories(
        ${PROJECT_SOURCE_DIR}/src/
)
file(GLOB src_executable
        ${PROJECT_SOURCE_DIR}/src/*.cpp
        )
add_executable(code ${src_dir} ${src_executable})