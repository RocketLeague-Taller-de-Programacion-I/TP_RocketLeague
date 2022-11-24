//
// Created by lucaswaisten on 16/11/22.
//

#ifndef ROCKETLEAGUE_ACTIONLIST_H
#define ROCKETLEAGUE_ACTIONLIST_H


#include "ActionUpdate.h"

class ActionList : public ActionUpdate {

public:
    explicit ActionList(uint8_t& id, std::string& gamesList);
    ~ActionList() override;

    uint8_t getIdCreatorGame() override;
    uint8_t getType() const override;

    Action * execute(GameManager &manager, const std::function<BlockingQueue<Action *> *(ProtectedQueue<Action *> *)> &setQueue) override;
    std::vector<uint8_t> beSerialized() override;

    std::string getReturnMessage() override;
};


#endif //ROCKETLEAGUE_ACTIONLIST_H
