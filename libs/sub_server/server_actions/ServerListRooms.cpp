//
// Created by roby on 24/11/22.
//

#include "ServerListRooms.h"
#include "sub_server/gameManager.h"


std::shared_ptr<ServerUpdate> ServerListRooms::execute(GameManager &manager, const std::function<BlockingQueue<std::shared_ptr<ServerUpdate>> *(
        ProtectedQueue<std::shared_ptr<ServerAction>> *)> &setQueue) {

    std::vector<uint8_t> listData;
    uint8_t numberOfGames = manager.listGames(id, listData);
    uint8_t returnCode = numberOfGames ? OK : ERROR_FULL; //TODO: change ERROR_FULL to ERROR_EMPTY
    std::shared_ptr<ServerUpdate> update = std::make_shared<ServerListACK>(id, returnCode, numberOfGames, listData);
    return update;
}

void ServerListRooms::execute(Match &match) {

}
