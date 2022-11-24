//
// Created by roby on 22/11/22.
//

#ifndef ROCKETLEAGUE_ACTIONCREATEROOM_H
#define ROCKETLEAGUE_ACTIONCREATEROOM_H

#include "ClientAction.h"

// create ActionCreateRoom class with public inheritance from Action class
class ActionCreateRoom : public ClientAction{
private:
    uint8_t capacity;
    const std::string name;
public:

    explicit ActionCreateRoom(uint8_t &capacity, const std::string &name);
    ~ActionCreateRoom() override;

    uint8_t getType() const override;
    std::vector<uint8_t> beSerialized() override;

    uint8_t getCapacity();
    std::string getGameName();
};

#endif //ROCKETLEAGUE_ACTIONCREATEROOM_H
