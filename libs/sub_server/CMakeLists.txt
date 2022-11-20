add_library(lib_server
        Server.cpp
        Server.h
        gameManager.cpp
        gameManager.h
        game.cpp game.h
        ClientManager.cpp
        ClientManager.h
        Ball.cpp
        Ball.h
        Car.cpp
        Car.h
        Match.cpp
        Match.h
        MyContactListener.cpp
        MyContactListener.h
        )

target_link_libraries(lib_server lib_common)