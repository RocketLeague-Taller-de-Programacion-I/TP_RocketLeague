//
// Created by roby on 24/11/22.
//

#include "ServerJoinRoom.h"
#include "sub_server/gameManager.h" //TODO: reever esto

ServerJoinRoom::ServerJoinRoom(uint8_t &id, std::string &data) : ServerAction(id, data) {}

ServerUpdate * ServerJoinRoom::execute(GameManager &manager, const std::function<BlockingQueue<ServerUpdate *> *(
        ProtectedQueue<ServerAction *> *)> &setQueue) {
    std::string message = "OK";
    if(!manager.joinGame(id, roomName, setQueue)) {
        message = "ERROR";
    }
    return new ServerJoinACK(id, message);
}
