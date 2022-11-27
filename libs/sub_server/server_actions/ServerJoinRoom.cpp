//
// Created by roby on 24/11/22.
//

#include "ServerJoinRoom.h"
#include "sub_server/gameManager.h" //TODO: reever esto

ServerJoinRoom::ServerJoinRoom(const uint8_t &id, std::string &data) : ServerAction(id, data) {}

ServerUpdate * ServerJoinRoom::execute(GameManager &manager, const std::function<BlockingQueue<ServerUpdate *> *(
        ProtectedQueue<ServerAction *> *)> &setQueue) {

    uint8_t returnCode = manager.joinGame(id, roomName, setQueue) ? OK : ERROR_FULL;
    return new ServerJoinACK(id, returnCode);
}
