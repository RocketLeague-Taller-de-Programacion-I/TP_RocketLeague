//
// Created by lucaswaisten on 07/11/22.
//

#ifndef ROCKETLEAGUE_CLIENTMANAGER_H
#define ROCKETLEAGUE_CLIENTMANAGER_H


#include "../sub_common/thread.h"
#include "../sub_common/socket.h"
#include "gameManager.h"

class ClientManager : public Thread{
private:
    Socket &client;
    GameManager &gameManager;
    bool closed;
public:
    ClientManager(Socket &aClient, GameManager &aGameManager);

    void run();

    bool joinThread();

    bool endManager();
};


#endif //ROCKETLEAGUE_CLIENTMANAGER_H
