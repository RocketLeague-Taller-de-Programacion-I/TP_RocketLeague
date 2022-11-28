//
// Created by roby on 22/11/22.
//

#ifndef ROCKETLEAGUE_ACTIONJOINROOM_H
#define ROCKETLEAGUE_ACTIONJOINROOM_H

#include "ClientAction.h"

class ActionJoinRoom : public ClientAction{
private:
    std::string roomName;
public:
    explicit ActionJoinRoom(std::string &roomName);

    ~ActionJoinRoom() override;
    uint8_t getType() const override;

    std::vector<uint8_t> beSerialized() override;

    std::string getRoomName();
};


#endif //ROCKETLEAGUE_ACTIONJOINROOM_H
