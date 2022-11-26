//
// Created by roby on 24/11/22.
//

#ifndef ROCKETLEAGUE_SERVERACTION_H
#define ROCKETLEAGUE_SERVERACTION_H

class GameManager; //TODO: reveer esto

#include <cstdint>
#include <string>
#include <functional>

#include "sub_common/BlockingQueue.h"
#include "sub_common/ProtectedQueue.h"
#include "sub_server/server_updates/ServerUpdate.h"

enum actionType {
    CREATE_ROOM = 1,
    JOIN_ROOM,
    LIST_ROOMS,
    MOVE,
    UPDATE
};

class ServerAction {
protected:
    uint8_t id;
    std::string roomName;
public:
    ServerAction() = default;
    ServerAction(uint8_t &id) : id(id) {};
    ServerAction(uint8_t& id, std::string &roomName) : id(id), roomName(roomName){};
    virtual ~ServerAction() = default;

    virtual uint8_t getId() const { return id;};
    virtual std::string getRoomName() const { return roomName;};

    virtual ServerUpdate * execute(GameManager &manager, const std::function<BlockingQueue<ServerUpdate *> *(
            ProtectedQueue<ServerAction *> *)> &setQueue) = 0;
};


#endif //ROCKETLEAGUE_SERVERACTION_H

//ServerAction
// ActionCreateRoom
//  - id
//  - name
//  - maxPlayers
// ActionJoinRoom
//  - id
//  - name
// ActionListRooms
//  - id
// ActionMove

//ServerUpdate
// CreateACK
// JoinACK
// ListACK
// WorldUpdate