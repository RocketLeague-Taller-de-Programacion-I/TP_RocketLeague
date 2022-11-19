//
// Created by roby on 19/11/22.
//

#ifndef ROCKETLEAGUE_ACTIONUPDATE_H
#define ROCKETLEAGUE_ACTIONUPDATE_H



#include "Action.h"

class ActionUpdate : public Action {

public:
    ActionUpdate(uint8_t id, std::string name);

    void execute(GameManager &gameManager, std::function<void(BlockingQueue<Action> *)> setQueue) override;
    std::string getGameName() override;

    uint8_t getIdCreatorGame() override;
};


#endif //ROCKETLEAGUE_ACTIONUPDATE_H
