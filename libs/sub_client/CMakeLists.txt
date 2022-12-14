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
        client_sdl/sprites/GameSprite.h
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
        client_updates/ClientCreateACK.h
        client_updates/ClientJoinACK.h
        client_updates/ClientListACK.cpp
        client_updates/ClientListACK.h
        client_updates/ClientStartedGameACK.h
        client_updates/ClientUpdateWorld.cpp
        client_updates/ClientUpdateWorld.h
        client_updates/ClientUpdateStats.h
        client_sdl/Ball.h
        client_sdl/Score.h
        client_sdl/Car.h
        client_sdl/GameTime.h
        client_sdl/sprites/BallSprite.cpp
        client_sdl/sprites/BallSprite.h
        client_sdl/sprites/ScoreSprite.cpp
        client_sdl/sprites/ScoreSprite.h
        client_sdl/sprites/CarSprite.cpp
        client_sdl/sprites/CarSprite.h
        client_sdl/sprites/GameTimeSprite.cpp
        client_sdl/sprites/GameTimeSprite.h
        client_sdl/sprites/GameStatsSprite.cpp
        client_sdl/sprites/GameStatsSprite.h)

target_link_libraries(lib_client SDL2pp::SDL2pp Qt5::Widgets)
