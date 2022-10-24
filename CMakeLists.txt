cmake_minimum_required(VERSION 3.16 FATAL_ERROR)
project(RocketLeague LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -pedantic -pedantic-errors -O3 -ggdb -DDEBUG -fno-inline")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})
#  Incluyo los subdir.
add_subdirectory("sub_client")
add_subdirectory("sub_server")

#  Creo los ejecutables
add_executable(client client_main.cpp)
add_executable(server server_main.cpp)

#  Linkeo las bibliotecas con los ejecutables
target_link_libraries(server lib_server)
target_link_libraries(client lib_client)