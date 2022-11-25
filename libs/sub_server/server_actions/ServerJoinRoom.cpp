//
// Created by roby on 24/11/22.
//

#include "ServerJoinRoom.h"
#include "sub_server/gameManager.h" //TODO: reever esto

ServerJoinRoom::ServerJoinRoom(uint8_t &id, std::string &data) : ServerAction(id, data) {}

ServerUpdate * ServerJoinRoom::execute(GameManager &manager, const std::function<BlockingQueue<ServerUpdate *> *(
        ProtectedQueue<ServerAction *> *)> &setQueue) {
    std::string returnMessage = "OK";
    std::vector<uint8_t> returnData = std::vector<uint8_t>(returnMessage.begin(), returnMessage.end());
    if(!manager.joinGame(id, roomName, setQueue)) {
        returnMessage = "ERROR";
        returnData = std::vector<uint8_t>(returnMessage.begin(), returnMessage.end());
    }
    return new ServerJoinACK(id, returnData);
}
