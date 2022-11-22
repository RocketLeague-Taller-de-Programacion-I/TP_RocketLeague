//
// Created by lucaswaisten on 16/11/22.
//

#ifndef ROCKETLEAGUE_ACTIONCREATESERVER_H
#define ROCKETLEAGUE_ACTIONCREATESERVER_H

#include "../sub_common/sub_action/Action.h"
#include "gameManager.h"


class ActionCreateServer : public Action {
public:
    explicit ActionCreateServer(uint8_t &id, int &c, const std::string &name, GameManager &gameManager,
                                std::function<void(BlockingQueue<Action *> *, BlockingQueue<Action *> *)> function);

    int getCapacity() const;

    std::string getGameName();

    void execute() override;
    std::vector<uint8_t>

    beSerialized() override;

    ~ActionCreateServer() override;

private:
    GameManager &gameManager;
    std::function<void(BlockingQueue<Action *> *, BlockingQueue<Action *> *)> startClientThreads;
    int &capacityGame;
    const std::string &nameGame;
};


#endif //ROCKETLEAGUE_ACTIONCREATESERVER_H
