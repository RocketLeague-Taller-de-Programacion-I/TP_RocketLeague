//
// Created by roby on 19/11/22.
//

#ifndef ROCKETLEAGUE_ACTIONUPDATE_H
#define ROCKETLEAGUE_ACTIONUPDATE_H

#include "Action.h"

class ActionUpdate : public Action {
public:
    ActionUpdate(uint8_t& id, std::string& returnMessage);
    ~ActionUpdate() override;

    std::string getGameName();
    uint8_t getId() override;
    void execute() override;
    std::vector<uint8_t> beSerialized() override;

    uint8_t getX();
    uint8_t getY();
    uint8_t getAngle();
private:
    std::string &nameGame;
};


#endif //ROCKETLEAGUE_ACTIONUPDATE_H
