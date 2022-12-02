//
// Created by roby on 24/11/22.
//

#include "ServerListRooms.h"
#include "sub_server/gameManager.h"


void
ServerListRooms::execute(std::function<void(ProtectedQueue<std::shared_ptr<ServerAction>> *,
                                            BlockingQueue<std::shared_ptr<ServerUpdate>> *)> &startThreadsCallable,
                         std::function<void(void *, unsigned int)> &sendCallable,
                         ServerProtocolo &protocolo) {

    std::vector<uint8_t> listData;
    uint8_t numberOfGames = manager.listGames(id, listData);
    uint8_t returnCode = numberOfGames ? OK : ERROR_FULL; //TODO: change ERROR_FULL to ERROR_EMPTY
    std::shared_ptr<ServerUpdate> update = std::make_shared<ServerListACK>(id, returnCode, numberOfGames, listData);
    update->beSerialized(&protocolo, sendCallable);
}

void ServerListRooms::execute(Match &match) {

}
