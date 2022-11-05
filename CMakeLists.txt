cmake_minimum_required(VERSION 3.16 FATAL_ERROR)

project(RocketLeague LANGUAGES CXX)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -pedantic -pedantic-errors -O3 -ggdb -DDEBUG -fno-inline")
set(CMAKE_CXX_STANDARD 17)

set(SDL2PP_WITH_IMAGE ON) # if you need SDL_image support
set(SDL2PP_WITH_MIXER ON) # if you need SDL_mixer support
set(SDL2PP_WITH_TTF ON) # if you need SDL_ttf support
add_subdirectory(libs/libSDL2pp)

add_subdirectory(box2d)

# Incluyo libreria SDL2pp y box2d
message("Agregando '${PROJECT_SOURCE_DIR}/libs' como directorio de includes")
include_directories(${PROJECT_SOURCE_DIR}/libs)
include_directories(${PROJECT_SOURCE_DIR}/box2d/include)
include_directories(${SDL2PP_INCLUDE_DIRS})

#  Incluyo los subdir.
add_subdirectory("sub_client")
add_subdirectory("sub_server")

#  Creo los ejecutables
#add_executable(client client_main.cpp  ${SUB_CLIENT_VAR} ${UIS_HEADERS})
add_executable(server server_main.cpp)
#find_package(SDL2pp REQUIRED)
find_package(Qt5 REQUIRED COMPONENTS Widgets)
#  Linkeo las bibliotecas con los ejecutables
target_link_libraries(server PUBLIC lib_server box2d Qt5::Widgets)
target_link_libraries(client PUBLIC lib_client SDL2pp::SDL2pp Qt5::Widgets)

