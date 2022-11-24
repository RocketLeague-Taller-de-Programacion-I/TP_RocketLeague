//
// Created by roby on 19/11/22.
//

#ifndef ROCKETLEAGUE_ACTIONUPDATE_H
#define ROCKETLEAGUE_ACTIONUPDATE_H

#include "Action.h"

class ActionUpdate : public Action {
private:
public:
    ActionUpdate(uint8_t& id, std::string& returnMessage);
    ~ActionUpdate() override;

    std::string getGameName() override;
    uint8_t getIdCreatorGame() override;
    uint8_t getType() const override;

    Action * execute(GameManager &gameManager, const std::function<BlockingQueue<Action *> *(ProtectedQueue<Action *> *)> &setQueue) override;
    std::vector<uint8_t> beSerialized() override;
    std::string getReturnMessage() override;

    uint8_t getX();
    uint8_t getY();
    uint8_t getAngle();
};


#endif //ROCKETLEAGUE_ACTIONUPDATE_H
