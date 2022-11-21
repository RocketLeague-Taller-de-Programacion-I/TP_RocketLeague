//
// Created by lucaswaisten on 16/11/22.
//

#ifndef ROCKETLEAGUE_ACTIONCREATE_H
#define ROCKETLEAGUE_ACTIONCREATE_H

#include "../BlockingQueue.h"
#include "Action.h"

class ActionCreate : public Action {
public:
    explicit ActionCreate(uint8_t &id, uint8_t &c, const std::string &name);
    ~ActionCreate() override;

    std::string getGameName() override;

    void execute(GameManager &gameManager, const std::function<void(BlockingQueue<Action *> *,BlockingQueue<Action *> *)> &setQueue) override;
    std::vector<uint8_t> beSerialized() override;

    uint8_t getCapacity() override;
    uint8_t getIdCreatorGame() override;
    uint8_t getType() const override;

};


#endif //ROCKETLEAGUE_ACTIONCREATE_H
