//
// Created by roby on 24/11/22.
//

#include "ServerJoinRoom.h"
#include "sub_server/gameManager.h" //TODO: reever esto

void
ServerJoinRoom::execute(std::function<void(ProtectedQueue<std::shared_ptr<ServerAction>> *,
                                           BlockingQueue<std::shared_ptr<ServerUpdate>> *)> &startThreadsCallable,
                        std::function<void(void *, unsigned int)> &sendCallable,
                        ServerProtocolo &protocolo) {

    uint8_t returnCode = manager.joinGame(id, roomName, startThreadsCallable) ? OK : ERROR_FULL;
    std::shared_ptr<ServerUpdate> update = std::make_shared<ServerJoinACK>(id, returnCode);
    update->beSerialized(&protocolo, sendCallable);
}

void ServerJoinRoom::execute(Match &match) {}
