//
// Created by roby on 22/11/22.
//

#ifndef ROCKETLEAGUE_CLIENTPROTOCOL_H
#define ROCKETLEAGUE_CLIENTPROTOCOL_H

#include "sub_client/client_updates/ClientCreateACK.h"
#include "sub_client/client_updates/ClientJoinACK.h"
#include "sub_client/client_updates/ClientListACK.h"

#include "sub_client/client_actions/ClientAction.h"

class ClientProtocol {
private:
    static ClientUpdate* parseCreateACK(const std::vector<uint8_t> &data);
    static ClientUpdate* parseJoinACK(const std::vector<uint8_t> &data);
    static ClientUpdate* parseListUpdate(const std::vector<uint8_t> &data);
    static ClientUpdate* parseWorldUpdate(const std::vector<uint8_t> &vector);

public:
    static ClientUpdate* deserializeData(const std::vector<uint8_t>& data);
};


#endif //ROCKETLEAGUE_CLIENTPROTOCOL_H
