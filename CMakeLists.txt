cmake_minimum_required(VERSION 3.7)

project(aguil)

# For windows
if (WIN32)
    set(CMAKE_PREFIX_PATH "C:/SDKS/SDL2/64/lib/cmake")
endif()

find_package(SDL2 REQUIRED)
include_directories(include ${SDL2_INCLUDE_DIRS})
file(GLOB_RECURSE SOURCES src/*.c)

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES} SDL2_ttf)

