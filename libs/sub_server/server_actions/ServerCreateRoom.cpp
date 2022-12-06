//
// Created by roby on 24/11/22.
//

#include "ServerCreateRoom.h"
#include "sub_server/gameManager.h" //TODO: reever esto

void
ServerCreateRoom::execute(std::function<void(ProtectedQueue<std::shared_ptr<ServerAction>> *,
                                             BlockingQueue<std::optional<std::shared_ptr<ServerUpdate>>> *)> &startThreadsCallable,
                          std::function<void(void *, unsigned int)> &sendCallable,
                          ServerProtocolo &protocolo) {

    uint8_t returnCode = manager.createGame(id, capacity, roomName, startThreadsCallable) ? ERROR_FULL : OK;
    std::shared_ptr<ServerUpdate> update = std::make_shared<ServerCreateACK>(id, returnCode);
    update->beSerialized(&protocolo, sendCallable);
}

void ServerCreateRoom::execute(Match &match) {

}
