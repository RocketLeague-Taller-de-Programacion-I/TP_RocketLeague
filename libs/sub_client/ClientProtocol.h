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

#include "sub_client/client_actions/ClientAction.h"

class ClientProtocol {
private:
    static ClientUpdate *parseCreateACK(const std::function<void(void *, int)> &receiveBytes);
    static ClientUpdate* parseJoinACK(const std::function<void(void *, int)> &receiveBytes);
    static ClientUpdate* parseListUpdate(const std::function<void(void *, int)> &receiveBytes);
    static ClientUpdate* parseWorldUpdate(const std::vector<uint8_t> &vector);

public:
//    static ClientUpdate* deserializeData(const std::vector<uint8_t>& data);

    static ClientUpdate *deserializeCreateACK(const std::vector<uint16_t> &data);

    static ClientUpdate *deserializeData(const uint8_t &type,
                                         const std::function<void(void *, int)> &receiveBytes);

   // static void receiveBytes(std::vector<uint8_t> &data, uint8_t &size);

    static ClientUpdate *parseStartedGameACK(const std::function<void(std::vector<uint8_t> &, uint8_t &)> &function);
};


#endif //ROCKETLEAGUE_CLIENTPROTOCOL_H
