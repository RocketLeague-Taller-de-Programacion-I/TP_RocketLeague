add_library(lib_server
        Server.cpp
        Server.h
        gameManager.cpp
        gameManager.h
        game.cpp game.h
        ClientManager.cpp
        ClientManager.h
        Ball.cpp Ball.h Car.cpp Car.h Match.cpp Match.h MyContactListener.cpp MyContactListener.h
        ClientReceiver.cpp
        ClientReceiver.h
        ClientSender.cpp
        ClientSender.h
        protocolo.cpp
        protocolo.h
        server_actions/ServerAction.h
        server_actions/ServerCreateRoom.cpp
        server_actions/ServerCreateRoom.h
        server_actions/ServerJoinRoom.cpp
        server_actions/ServerJoinRoom.h
        server_actions/ServerListRooms.cpp
        server_actions/ServerListRooms.h
        server_updates/ServerUpdate.h
        server_updates/ServerCreateACK.cpp
        server_updates/ServerCreateACK.h
        server_updates/ServerJoinACK.cpp
        server_updates/ServerJoinACK.h
        server_updates/ServerListACK.cpp
        server_updates/ServerListACK.h)

target_link_libraries(lib_server lib_common)