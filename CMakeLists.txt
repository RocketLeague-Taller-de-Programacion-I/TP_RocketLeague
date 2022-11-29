cmake_minimum_required(VERSION 3.16 FATAL_ERROR)

project(RocketLeague LANGUAGES CXX)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  -pedantic -pedantic-errors -O3 -ggdb -DDEBUG -fno-inline -pthread")
set(CMAKE_CXX_STANDARD 17)

set(SDL2PP_WITH_IMAGE ON) # if you need SDL_image support
set(SDL2PP_WITH_MIXER ON) # if you need SDL_mixer support
set(SDL2PP_WITH_TTF ON) # if you need SDL_ttf support
add_subdirectory(libs/libSDL2pp)

add_subdirectory(box2d)
add_subdirectory(libs/Catch2)

# Incluyo libreria SDL2pp y box2d
message("General - Agregando '${PROJECT_SOURCE_DIR}/libs' como directorio de includes")
include_directories(${PROJECT_SOURCE_DIR}/libs)
include_directories(${PROJECT_SOURCE_DIR}/box2d/include)
include_directories(${SDL2PP_INCLUDE_DIRS})
include_directories(${PROJECT_BINARY_DIR})
#  Incluyo los subdir.
add_subdirectory(libs/sub_client)
add_subdirectory(libs/sub_server)
add_subdirectory(libs/sub_common)
add_subdirectory(tests)

# Find the QtWidgets library
find_package(Qt5 REQUIRED COMPONENTS Widgets)
qt5_wrap_ui(UIS_HEADERS
        ui/mainwindow.ui
        )

#  Creo los ejecutables
add_executable(client_main client_main.cpp ${UIS_HEADERS})
add_executable(server_main server_main.cpp)

#  Linkeo las bibliotecas con los ejecutables
target_link_libraries(server_main PUBLIC lib_server lib_common box2d Qt5::Widgets)
target_link_libraries(client_main PUBLIC lib_client lib_common SDL2pp::SDL2pp Qt5::Widgets)

