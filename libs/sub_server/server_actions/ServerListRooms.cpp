//
// Created by roby on 24/11/22.
//

#include "ServerListRooms.h"
#include "sub_server/gameManager.h"


ServerUpdate * ServerListRooms::execute(GameManager &manager, const std::function<BlockingQueue<ServerUpdate *> *(
        ProtectedQueue<ServerAction *> *)> &setQueue) {
    std::string list = manager.listGames(id);
    std::vector<uint8_t> returndata(list.begin(), list.end());
    return new ServerListACK(id, returndata);
}
