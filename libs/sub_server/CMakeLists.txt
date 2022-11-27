add_library(lib_server
        Server.cpp
        Server.h
        gameManager.cpp
        gameManager.h
        game.cpp game.h
        ClientManager.cpp
        ClientManager.h
        server_box2d/Ball.cpp server_box2d/Ball.h server_box2d/Car.cpp server_box2d/Car.h server_box2d/Match.cpp server_box2d/Match.h server_box2d/MyContactListener.cpp server_box2d/MyContactListener.h
        ClientReceiver.cpp
        ClientReceiver.h
        ClientSender.cpp
        ClientSender.h
        ServerProtocolo.cpp
        ServerProtocolo.h
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
        server_updates/ServerListACK.h
        server_updates/ServerUpdateWorld.cpp
        server_updates/ServerUpdateWorld.h)

target_link_libraries(lib_server lib_common)