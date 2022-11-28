//
// Created by roby on 24/11/22.
//

#include "ServerCreateRoom.h"
#include "sub_server/gameManager.h" //TODO: reever esto

ServerCreateRoom::ServerCreateRoom(const uint8_t &id, uint8_t &capacity, std::string &data) : ServerAction(id, data) , capacity(capacity) {}

std::shared_ptr<ServerUpdate> ServerCreateRoom::execute(GameManager &manager, const std::function<BlockingQueue<std::shared_ptr<ServerUpdate>> *(
        ProtectedQueue<std::shared_ptr<ServerAction>> *)> &setQueue) {

    uint8_t returnCode = manager.createGame(id, capacity, roomName, setQueue) ? OK : ERROR_FULL;
//    return new ServerCreateACK(id, returnMessage);
    std::shared_ptr<ServerUpdate> update = std::make_shared<ServerCreateACK>(id, returnCode);
    return update;
}

void ServerCreateRoom::execute(Match &match) {

}
