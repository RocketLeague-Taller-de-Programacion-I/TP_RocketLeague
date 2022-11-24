//
// Created by roby on 24/11/22.
//

#include "ServerCreateRoom.h"
#include "sub_server/gameManager.h" //TODO: reever esto

ServerCreateRoom::ServerCreateRoom(uint8_t &id, uint8_t &capacity, std::string &data) : ServerAction(id, data) , capacity(capacity) {}

ServerUpdate * ServerCreateRoom::execute(GameManager &manager, const std::function<BlockingQueue<ServerUpdate *> *(
        ProtectedQueue<ServerAction *> *)> &setQueue) {
    std::string returnMessage = "OK";
    if(!manager.createGame(id, capacity, roomName, setQueue)) {
        returnMessage = "ERROR";
    }
    return new ServerCreateACK(id, returnMessage);
}
