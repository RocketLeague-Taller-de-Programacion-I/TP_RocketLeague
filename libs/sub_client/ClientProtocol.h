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

#include "sub_client/client_actions/ActionCreateRoom.h"
#include "sub_client/client_actions/ActionJoinRoom.h"
#include "sub_client/client_actions/ActionListRooms.h"
#include "sub_client/client_actions/ClientActionMove.h"

class ClientProtocol {
private:
    static std::shared_ptr<ClientUpdate> parseCreateACK(const std::function<void(void *, int)> &receiveBytes);
    static std::shared_ptr<ClientUpdate> parseJoinACK(const std::function<void(void *, int)> &receiveBytes);
    static std::shared_ptr<ClientUpdate> parseListUpdate(const std::function<void(void *, int)> &receiveBytes);
    static std::shared_ptr<ClientUpdate> parseWorldUpdate(const std::function<void(void *, int)> &receiveBytes);

    const std::function<void(void *, unsigned int)> &sendBytes;
public:
    ClientProtocol(const std::function<void(void *, unsigned int)> &sendBytesCallable) : sendBytes(sendBytesCallable) {};
    static std::shared_ptr<ClientUpdate> deserializeData(const uint8_t &type,
                                                         const std::function<void(void *, int)> &receiveBytes);

   // static void receiveBytes(std::vector<uint8_t> &data, uint8_t &size);
    void serializeAction(std::shared_ptr<ClientAction> action);
    void serializeCreateRoom(ActionCreateRoom *action);
    void serializeJoinRoom(ActionJoinRoom *action);
    void serializeListRooms(ActionListRooms *action);
    void serializeMove(ClientActionMove *action);
};


#endif //ROCKETLEAGUE_CLIENTPROTOCOL_H
