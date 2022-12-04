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
        client_sdl/Animation.cpp
        client_sdl/Animation.h
        client_sdl/Player.cpp
        client_sdl/Player.h
        client_sdl/GameLoop.cpp
        client_sdl/GameLoop.h
        client_qt/mainwindow.cpp
        client_qt/mainwindow.h
        client_qt/Button.cpp
        client_qt/Button.h
        GameRenderer.cpp
        GameRenderer.h
        client_sdl/Worldview.cpp
        client_sdl/Worldview.h
        client_sdl/GameSprite.cpp
        client_sdl/GameSprite.h
        UpdatesReceiverThread.cpp
        UpdatesReceiverThread.h
        ActionsSenderThread.cpp
        ActionsSenderThread.h
        ClientProtocol.cpp
        ClientProtocol.h
        client_actions/ClientAction.h
        client_actions/ClientActionMove.cpp
        client_actions/ClientActionMove.h
        client_actions/ActionCreateRoom.cpp
        client_actions/ActionCreateRoom.h
        client_actions/ActionJoinRoom.cpp
        client_actions/ActionJoinRoom.h
        client_actions/ActionListRooms.cpp
        client_actions/ActionListRooms.h
        client_updates/ClientUpdate.cpp
        client_updates/ClientUpdate.h
        client_updates/ClientCreateACK.cpp
        client_updates/ClientCreateACK.h
        client_updates/ClientJoinACK.cpp
        client_updates/ClientJoinACK.h
        client_updates/ClientListACK.cpp
        client_updates/ClientListACK.h
        WaitingForGameToStartThread.cpp
        WaitingForGameToStartThread.h
        client_updates/ClientStartedGameACK.cpp
        client_updates/ClientStartedGameACK.h
        client_updates/ClientUpdateWorld.cpp
        client_updates/ClientUpdateWorld.h
        client_sdl/Car.cpp
        client_sdl/Car.h
        client_sdl/Score.cpp
        client_sdl/Score.h
        client_sdl/Ball.h
        client_sdl/ScoreSprite.cpp
        client_sdl/ScoreSprite.h
        client_sdl/CarSprite.cpp
        client_sdl/CarSprite.h
        client_sdl/BallSprite.cpp
        client_sdl/BallSprite.h
        client_sdl/GameTimeSprite.cpp
        client_sdl/GameTimeSprite.h
        client_sdl/GameTime.cpp
        client_sdl/GameTime.h)

target_link_libraries(lib_client SDL2pp::SDL2pp Qt5::Widgets)
