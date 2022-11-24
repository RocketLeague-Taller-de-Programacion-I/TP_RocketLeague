//
// Created by roby on 22/11/22.
//

#ifndef ROCKETLEAGUE_CLIENTPROTOCOL_H
#define ROCKETLEAGUE_CLIENTPROTOCOL_H

#include "CreateACK.h"
#include "JoinACK.h"
#include "ListACK.h"

#include "ClientAction.h"

class ClientProtocol {
private:
    static GameUpdate* parseCreateACK(const std::vector<uint8_t> &data);
    static GameUpdate* parseJoinACK(const std::vector<uint8_t> &data);
    static GameUpdate* parseListUpdate(const std::vector<uint8_t> &data);
    static GameUpdate* parseWorldUpdate(const std::vector<uint8_t> &vector);

public:
    static GameUpdate* deserializeData(const std::vector<uint8_t>& data);
};


#endif //ROCKETLEAGUE_CLIENTPROTOCOL_H
