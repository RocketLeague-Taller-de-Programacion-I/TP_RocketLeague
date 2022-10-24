cmake_minimum_required(VERSION 3.16 FATAL_ERROR)
project(RocketLeague LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
#  Creo los ejecutables
add_executable(lib_client client_main.cpp)
add_executable(lib_server server_main.cpp)
#  Incluyo los subdir.
include_directories(${PROJECT_SOURCE_DIR}/lib_client)
include_directories(${PROJECT_SOURCE_DIR}/lib_server)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -pedantic -pedantic-errors -O3 -ggdb -DDEBUG -fno-inline")
#  Linkeo las bibliotecas con los ejecutables
target_link_libraries(lib_server server)
target_link_libraries(lib_client client)