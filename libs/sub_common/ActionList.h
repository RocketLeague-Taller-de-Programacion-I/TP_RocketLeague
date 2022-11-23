//
// Created by lucaswaisten on 16/11/22.
//

#ifndef ROCKETLEAGUE_ACTIONLIST_H
#define ROCKETLEAGUE_ACTIONLIST_H

#include "Action.h"

class ActionList : public Action{

public:
    explicit ActionList(uint8_t id);
    ~ActionList() override;

    uint8_t getIdCreatorGame() override;
    uint8_t getType() const override;

    void execute(GameManager &manager, const std::function<void(BlockingQueue<Action *> *,BlockingQueue<Action *> *)> &setQueue) override;
    std::vector<uint8_t> beSerialized() override;
};


#endif //ROCKETLEAGUE_ACTIONLIST_H