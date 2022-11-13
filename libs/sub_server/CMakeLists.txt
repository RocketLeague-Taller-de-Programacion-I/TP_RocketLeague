add_library(lib_server
        Server.cpp
        Server.h
        gameManager.cpp
        gameManager.h
        game.cpp game.h
        ClientManager.cpp
        ClientManager.h
        ClientReceiver.cpp
        ClientReceiver.h
        ClientSender.cpp
        ClientSender.h)

target_link_libraries(lib_server lib_common)