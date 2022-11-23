set(SDL2PP_WITH_IMAGE ON) # if you need SDL_image support
set(SDL2PP_WITH_MIXER ON) # if you need SDL_mixer support
set(SDL2PP_WITH_TTF ON) # if you need SDL_ttf support

# Habilito el automoc para poder hacer autoconnect de señales
set(CMAKE_AUTOMOC on)
# Habilito autorcc para manejar automaticamente los QResources
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC_SEARCH_PATHS ${PROJECT_SOURCE_DIR}/ui)
set(CMAKE_AUTOUIC ON)
find_package(Qt5Widgets)

message("Client - Agregando '${PROJECT_SOURCE_DIR}/sub_client' como directorio de includes")

#add_executable(client ../../client_main.cpp ${UIS_HEADERS})
#include_directories(${SDL2PP_INCLUDE_DIRS})
add_library(lib_client
        Client.cpp
        Client.h
        Animation.cpp
        Animation.h
        Player.cpp
        Player.h
        GameLoop.cpp
        GameLoop.h
        mainwindow.cpp
        mainwindow.h
        gamescene.cpp
        gamescene.h
        Button.cpp
        Button.h
        RenderThread.cpp
        RenderThread.h
        Worldview.cpp
        Worldview.h
        GameSprite.cpp
        GameSprite.h
        UpdatesReceiverThread.cpp
        UpdatesReceiverThread.h
        ThreadActionsSender.cpp
        ThreadActionsSender.h
        ClientAction.cpp
        ClientAction.h
        ActionCreateRoom.cpp
        ActionCreateRoom.h
        GameUpdate.cpp
        GameUpdate.h
        ActionJoinRoom.cpp
        ActionJoinRoom.h
        ActionListRooms.h
        ClientProtocol.cpp
        ClientProtocol.h)
target_link_libraries(lib_client SDL2pp::SDL2pp Qt5::Widgets)
