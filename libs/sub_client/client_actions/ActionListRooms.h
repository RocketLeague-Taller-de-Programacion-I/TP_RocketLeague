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

    std::vector<uint8_t> beSerialized()  override {
        std::vector<uint8_t> listData;
        listData.push_back(LIST);
        return listData;
    };
    uint8_t getType() const override {
        return LIST;
    };
};


#endif //ROCKETLEAGUE_ACTIONLISTROOMS_H
