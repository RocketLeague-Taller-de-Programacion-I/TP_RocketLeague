//
// Created by roby on 24/11/22.
//

#ifndef ROCKETLEAGUE_SERVERACTION_H
#define ROCKETLEAGUE_SERVERACTION_H

class GameManager; //TODO: reveer esto

#include <cstdint>
#include <string>
#include <functional>
#include <optional>
#include "sub_common/BlockingQueue.h"
#include "sub_common/ProtectedQueue.h"
#include "sub_server/server_updates/ServerUpdate.h"
#include "sub_server/server_box2d/Match.h"

enum actionType {
    CREATE_ROOM = 1,
    JOIN_ROOM,
    LIST_ROOMS,
    MOVE
};

enum direction {
    RIGHT_D,
    LEFT_D,
    JUMP_D,
    DOWN_D,
    TURBO_D
} ;

enum state : bool {
    ON = true,
    OFF = false
};

class ServerAction {
protected:
    uint8_t id;
    std::string roomName;
public:
    ServerAction() = default;
    explicit ServerAction(const uint8_t &id) : id(id) {};
    ServerAction(const uint8_t &id, std::string &roomName) : id(id), roomName(roomName){};
    virtual ~ServerAction() = default;

    virtual uint8_t getId() const { return id;};
    virtual std::string getRoomName() const { return roomName;};

    virtual void
        execute(std::function<void(ProtectedQueue<std::shared_ptr<ServerAction>> *,
                                   BlockingQueue<std::optional<std::shared_ptr<ServerUpdate>>> *)> &startThreadsCallable,
                std::function<void(void *, unsigned int)> &sendCallable,
                ServerProtocolo &protocolo) = 0;

    virtual void execute(Match& match) = 0;
};


#endif //ROCKETLEAGUE_SERVERACTION_H
