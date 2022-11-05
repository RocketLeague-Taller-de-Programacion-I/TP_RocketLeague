set(SDL2PP_WITH_IMAGE ON) # if you need SDL_image support
set(SDL2PP_WITH_MIXER ON) # if you need SDL_mixer support
set(SDL2PP_WITH_TTF ON) # if you need SDL_ttf support
#add_definitions(-DDATA_PATH="${PROJECT_SOURCE_DIR}/data")
set(CMAKE_AUTOUIC_SEARCH_PATHS ${PROJECT_SOURCE_DIR}/ui)
set(CMAKE_AUTOUIC ON)
find_package(Qt5Widgets)

message("Client - Agregando '${PROJECT_SOURCE_DIR}/sub_client' como directorio de includes")

#add_executable(client ../../client_main.cpp ${UIS_HEADERS})
#include_directories(${SDL2PP_INCLUDE_DIRS})
add_library(lib_client Client.cpp Client.h Animation.cpp Animation.h Player.cpp Player.h Greeter.h Greeter.cpp GameLoop.cpp GameLoop.h)
target_link_libraries(lib_client SDL2pp::SDL2pp Qt5::Widgets)
