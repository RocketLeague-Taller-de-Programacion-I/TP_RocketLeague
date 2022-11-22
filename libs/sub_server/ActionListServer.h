//
// Created by lucaswaisten on 16/11/22.
//

#ifndef ROCKETLEAGUE_ACTIONLISTSERVER_H
#define ROCKETLEAGUE_ACTIONLISTSERVER_H

#include "sub_common/Action.h"
#include "gameManager.h"

class ActionListServer : public Action{

public:
    explicit ActionListServer(uint8_t id, GameManager &manager,
                              std::function<void(BlockingQueue<Action *> *, BlockingQueue<Action *> *)> function);

    void execute() override;

    std::vector<uint8_t> beSerialized() override;

    ~ActionListServer() override;
private:
    GameManager &gameManager;
    std::function<void(BlockingQueue<Action *> *, BlockingQueue<Action *> *)> startClientThreads;
};


#endif //ROCKETLEAGUE_ACTIONLISTSERVER_H
