//
// Created by roby on 22/11/22.
//

#ifndef ROCKETLEAGUE_CLIENTPROTOCOL_H
#define ROCKETLEAGUE_CLIENTPROTOCOL_H

#include <iostream>
#include <map>
#include <memory>
#include "sub_client/client_updates/ClientCreateACK.h"
#include "sub_client/client_updates/ClientJoinACK.h"
#include "sub_client/client_updates/ClientListACK.h"
#include "sub_client/client_updates/ClientStartedGameACK.h"
#include "sub_client/client_updates/ClientUpdateWorld.h"
#include "sub_client/client_actions/ClientAction.h"

class ClientProtocol {
private:
    static std::shared_ptr<ClientUpdate> parseCreateACK(const std::function<void(void *, int)> &receiveBytes);
    static std::shared_ptr<ClientUpdate> parseJoinACK(const std::function<void(void *, int)> &receiveBytes);
    static std::shared_ptr<ClientUpdate> parseListUpdate(const std::function<void(void *, int)> &receiveBytes);
    static std::shared_ptr<ClientUpdate> parseWorldUpdate(const std::function<void(void *, int)> &receiveBytes);

public:

    static std::shared_ptr<ClientUpdate> deserializeData(const uint8_t &type,
                                                         const std::function<void(void *, int)> &receiveBytes);

};


#endif //ROCKETLEAGUE_CLIENTPROTOCOL_H
