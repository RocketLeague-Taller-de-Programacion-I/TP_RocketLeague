//
// Created by roby on 19/11/22.
//

#ifndef ROCKETLEAGUE_ACTIONUPDATE_H
#define ROCKETLEAGUE_ACTIONUPDATE_H



#include "Action.h"

class ActionUpdate : public Action {

public:
    ActionUpdate(uint8_t& id, std::string& name);
    ~ActionUpdate() override;

    std::string getGameName() override;
    void execute(GameManager &gameManager, const std::function<void(BlockingQueue<Action *> *, BlockingQueue<Action *> *)> &setQueue) override;
    std::vector<uint8_t> beSerialized() override;
};


#endif //ROCKETLEAGUE_ACTIONUPDATE_H
