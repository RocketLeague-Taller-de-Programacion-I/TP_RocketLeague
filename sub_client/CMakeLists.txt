set(SDL2PP_WITH_IMAGE ON) # if you need SDL_image support
set(SDL2PP_WITH_MIXER ON) # if you need SDL_mixer support
set(SDL2PP_WITH_TTF ON) # if you need SDL_ttf support
#add_definitions(-DDATA_PATH="${PROJECT_SOURCE_DIR}/data")
set(CMAKE_AUTOUIC ON)
find_package(Qt5Widgets)
include_directories(${PROJECT_SOURCE_DIR}/box2d/include)
include_directories(${SDL2PP_INCLUDE_DIRS})
add_library(lib_client Client.cpp Client.h Animation.cpp Animation.h Player.cpp Player.h mainwindow.cpp mainwindow.h mainwindow.ui)
target_link_libraries(lib_client SDL2pp::SDL2pp Qt5::Widgets)
