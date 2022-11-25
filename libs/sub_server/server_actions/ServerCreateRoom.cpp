//
// Created by roby on 24/11/22.
//

#include "ServerCreateRoom.h"
#include "sub_server/gameManager.h" //TODO: reever esto

ServerCreateRoom::ServerCreateRoom(uint8_t &id, uint8_t &capacity, std::string &data) : ServerAction(id, data) , capacity(capacity) {}

ServerUpdate * ServerCreateRoom::execute(GameManager &manager, const std::function<BlockingQueue<ServerUpdate *> *(
        ProtectedQueue<ServerAction *> *)> &setQueue) {
    std::string returnMessage = "OK";
    std::vector<uint8_t> returnData = std::vector<uint8_t>(returnMessage.begin(), returnMessage.end());
    if(!manager.createGame(id, capacity, roomName, setQueue)) {
        returnMessage = "ERROR";
        returnData = std::vector<uint8_t>(returnMessage.begin(), returnMessage.end());
    }
//    return new ServerCreateACK(id, returnMessage);
    return new ServerCreateACK(id, returnData);
}
