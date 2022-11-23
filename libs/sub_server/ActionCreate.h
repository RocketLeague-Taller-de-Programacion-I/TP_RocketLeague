//
// Created by lucaswaisten on 16/11/22.
//

#ifndef ROCKETLEAGUE_ACTIONCREATE_H
#define ROCKETLEAGUE_ACTIONCREATE_H


#include "Action.h"

class ActionCreate : public Action {
public:
    explicit ActionCreate(uint8_t &id, uint8_t &c, const std::string &name);
    ~ActionCreate() override;

    std::string getGameName() override;

    Action * execute(GameManager &gameManager, const std::function<BlockingQueue<Action *> *(
            ProtectedQueue<Action *> *)> &setQueue) override;
    std::vector<uint8_t> beSerialized() override;

    uint8_t getCapacity() override;
    uint8_t getIdCreatorGame() override;
    uint8_t getType() const override;

    std::string getReturnMessage() override;
};


#endif //ROCKETLEAGUE_ACTIONCREATE_H
