cmake_minimum_required(VERSION 3.24)
project(PAMSI_5_4)

set(CMAKE_CXX_STANDARD 17)
set(EXECUTABLE_NAME "PAMSI_5_4")

add_executable(PAMSI_5_4 main.cpp DFS.h Stack.h A*.h Node.h)

if(UNIX)
    set (CMAKE_PREFIX_PATH "/usr/lib/x86_64-linux-gnu/cmake/SFML" ${CMAKE_PREFIX_PATH})
endif(UNIX)

find_package(SFML 2 COMPONENTS graphics audio REQUIRED)
target_link_libraries(PAMSI_5_4 sfml-graphics sfml-audio)