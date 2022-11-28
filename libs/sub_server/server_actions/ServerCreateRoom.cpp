//
// Created by roby on 24/11/22.
//

#include "ServerCreateRoom.h"
#include "sub_server/gameManager.h" //TODO: reever esto

ServerCreateRoom::ServerCreateRoom(const uint8_t &id, uint8_t &capacity, std::string &data) : ServerAction(id, data) , capacity(capacity) {}

ServerUpdate * ServerCreateRoom::execute(GameManager &manager, const std::function<BlockingQueue<ServerUpdate *> *(
        ProtectedQueue<ServerAction *> *)> &setQueue) {

    uint8_t returnCode = manager.createGame(id, capacity, roomName, setQueue) ? OK : ERROR_FULL;
//    return new ServerCreateACK(id, returnMessage);
    return new ServerCreateACK(id, returnCode);
}

void ServerCreateRoom::execute(Match &match) {

}
