cmake_minimum_required(VERSION 3.7)

project(aguil)

find_package(SDL2 REQUIRED)
include_directories(include ${SDL2_INCLUDE_DIRS})
file(GLOB_RECURSE SOURCES src/*.c)

add_executable(${PROJECT_NAME} ${SOURCES})

#cmake -S ./ -B build -DCMAKE_C_COMPILER=clang -- So that we can use clang

target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES} SDL2_ttf)
