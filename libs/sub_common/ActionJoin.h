//
// Created by franco on 22/11/22.
//

#ifndef ROCKETLEAGUE_ACTIONJOIN_H
#define ROCKETLEAGUE_ACTIONJOIN_H


#include "Action.h"

class ActionJoin : public Action {
private:
    std::string gameName;
public:
    ActionJoin(uint8_t& id, std::string& name);
    ~ActionJoin() override;
    uint8_t getId() override;
    std::vector<uint8_t> beSerialized() override;

    std::string getGameName();
};


#endif //ROCKETLEAGUE_ACTIONJOIN_H
