//
// Created by roby on 22/11/22.
//

#ifndef ROCKETLEAGUE_ACTIONLISTROOMS_H
#define ROCKETLEAGUE_ACTIONLISTROOMS_H

#include "ClientAction.h"

class ActionListRooms : public ClientAction{
public:
    ActionListRooms() = default;
    ~ActionListRooms() override = default;

    uint8_t getType() const override;
    void beSerialized(ClientProtocol *protocolo) override;
};


#endif //ROCKETLEAGUE_ACTIONLISTROOMS_H
