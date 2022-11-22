//
// Created by franco on 22/11/22.
//

#ifndef ROCKETLEAGUE_ACTIONCREATE_H
#define ROCKETLEAGUE_ACTIONCREATE_H

#include "Action.h"

class ActionCreate : public Action {
private:
    uint8_t players;
    std::string gameName;
public:
    ActionCreate(uint8_t& id, uint8_t& players, std::string& name);
    ~ActionCreate() override;
    uint8_t getId() override;
    std::vector<uint8_t> beSerialized() override;

};


#endif //ROCKETLEAGUE_ACTIONCREATE_H
