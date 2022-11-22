//
// Created by lucaswaisten on 16/11/22.
//

#ifndef ROCKETLEAGUE_ACTIONJOINSERVER_H
#define ROCKETLEAGUE_ACTIONJOINSERVER_H

#include "sub_common/Action.h"
#include "gameManager.h"

class ActionJoinServer : public Action {

public:
    ActionJoinServer(uint8_t &id, std::string &name, GameManager &manager,
                     std::function<void(BlockingQueue<Action *> *, BlockingQueue<Action *> *)> function);

    std::string getGameName();

    void execute() override;

    std::vector<uint8_t> beSerialized() override;

    ~ActionJoinServer() override;
private:
    GameManager &gameManager;
    std::function<void(BlockingQueue<Action *> *, BlockingQueue<Action *> *)> startClientThreads;
    std::string &nameGame;
};


#endif //ROCKETLEAGUE_ACTIONJOINSERVER_H
