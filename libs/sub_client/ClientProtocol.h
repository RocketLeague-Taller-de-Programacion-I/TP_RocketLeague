//
// Created by roby on 22/11/22.
//

#ifndef ROCKETLEAGUE_CLIENTPROTOCOL_H
#define ROCKETLEAGUE_CLIENTPROTOCOL_H

#include <iostream>
#include <map>

#include "sub_client/client_updates/ClientCreateACK.h"
#include "sub_client/client_updates/ClientJoinACK.h"
#include "sub_client/client_updates/ClientListACK.h"
#include "sub_client/client_updates/ClientStartedGameACK.h"
#include "sub_client/client_updates/ClientUpdateWorld.h"

#include "sub_client/client_actions/ClientAction.h"

#include "sub_client/client_sdl/Ball.h"
#include "sub_client/client_sdl/Car.h"
#include "sub_client/client_sdl/Score.h"

enum action {
    RIGHT,
    LEFT,
    JUMP,
    DOWN,
    TURBO
};

enum state : bool {
    ON = true,
    OFF = false
};

class ClientProtocol {

private:
//    static ClientUpdate* deserializeData(const std::vector<uint8_t>& data);
    static ClientUpdate *parseCreateACK(const std::function<void(std::vector<uint8_t> &, uint8_t &)> &receiveBytes);
    static ClientUpdate* parseJoinACK(const std::function<void(std::vector<uint8_t> &, uint8_t &)> &receiveBytes);
    static ClientUpdate* parseListUpdate(const std::function<void(std::vector<uint8_t> &, uint8_t &)> &receiveBytes);
    static ClientUpdate *parseStartedGameACK(const std::function<void(std::vector<uint8_t> &, uint8_t &)> &receiveBytes);
    static ClientUpdate* parseWorldUpdate(const std::function<void(std::vector<uint8_t> &, uint8_t &)> &receiveBytes);

public:
    static ClientUpdate *deserializeCreateACK(const std::vector<uint8_t> &data);

    static ClientUpdate *deserializeData(const uint8_t &type,
                                         const std::function<void(std::vector<uint8_t> &, uint8_t &)> &receiveBytes);
};


#endif //ROCKETLEAGUE_CLIENTPROTOCOL_H
