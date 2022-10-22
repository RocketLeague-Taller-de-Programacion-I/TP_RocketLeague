cmake_minimum_required(VERSION 3.16 FATAL_ERROR)
project(RocketLeague LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
add_executable(server Server_main.cpp)
add_executable(client Client_main.cpp)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -pedantic -pedantic-errors -O3 -ggdb -DDEBUG -fno-inline")
