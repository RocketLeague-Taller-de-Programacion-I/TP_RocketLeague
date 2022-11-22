//
// Created by franco on 22/11/22.
//

#ifndef ROCKETLEAGUE_ACTIONLIST_H
#define ROCKETLEAGUE_ACTIONLIST_H


#include "Action.h"

class ActionList : public Action {
public:
    ActionList(uint8_t &id);
    ~ActionList();
    uint8_t getId() override;
    std::vector<uint8_t> beSerialized() override;
};


#endif //ROCKETLEAGUE_ACTIONLIST_H
