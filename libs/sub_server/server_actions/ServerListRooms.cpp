//
// Created by roby on 24/11/22.
//

#include "ServerListRooms.h"
#include "sub_server/gameManager.h"


ServerUpdate * ServerListRooms::execute(GameManager &manager, const std::function<BlockingQueue<ServerUpdate *> *(
        ProtectedQueue<ServerAction *> *)> &setQueue) {

    std::vector<uint8_t> listData;
    uint8_t numberOfGames = manager.listGames(id, listData);
    uint8_t returnCode = numberOfGames ? OK : ERROR_FULL; //TODO: change ERROR_FULL to ERROR_EMPTY
    return new ServerListACK(id, returnCode, numberOfGames, listData);
}

void ServerListRooms::execute(Match &match) {

}
