//
// Created by lucaswaisten on 04/11/22.
//

#include "ServerProtocolo.h"
#define INITIAL_POSITION 8
command_t ServerProtocolo::getMapCommand(uint32_t action) {
    return this->mapCommand.at(action);
}

std::shared_ptr<ServerAction> ServerProtocolo::deserializeData(const std::function<void(void *, int)> &receiveBytes) {
    return parseUpdateAction(receiveBytes);
}

std::shared_ptr<ServerAction> ServerProtocolo::parseUpdateAction(const std::function<void(void *, int)> &receiveBytes) {
    //id
    // direction or type of movement {Right, Left, Jump, Down, Turbo}
    // on or off
    uint8_t idPlayer;
    receiveBytes(&idPlayer, sizeof(idPlayer));

    uint8_t direction;
    receiveBytes(&direction, sizeof(direction));

    bool state;
    receiveBytes(&state, sizeof(state));

    std::shared_ptr<ServerAction> pAction = std::make_shared<ServerActionMove>(idPlayer, direction, state);
    return pAction;
}

void ServerProtocolo::serializeUpdate(std::shared_ptr<ServerUpdate> update,
                                      std::function<void(void *, unsigned int)> &sendCallable) {
    update->beSerialized(this, sendCallable);
}

void
ServerProtocolo::serializeCreateACK(ServerCreateACK *update, std::function<void(void *, unsigned int)> &sendBytes) {
    uint8_t type = update->getType();
    sendBytes(&type, sizeof(type));

    uint8_t id = update->getId();
    sendBytes(&id, sizeof(id));

    uint8_t returnCode = update->getReturnCode();
    sendBytes(&returnCode, sizeof(returnCode));
}

void ServerProtocolo::serializeJoinACK(ServerJoinACK *update, std::function<void(void *, unsigned int)> &sendBytes) {
    uint8_t type = update->getType();
    sendBytes(&type, sizeof(type));

    uint8_t id = update->getId();
    sendBytes(&id, sizeof(id));

    uint8_t returnCode = update->getReturnCode();
    sendBytes(&returnCode, sizeof(returnCode));
}

void
ServerProtocolo::serializeServerListACK(ServerListACK *update, std::function<void(void *, unsigned int)> &sendBytes) {
    uint8_t type = update->getType();
    sendBytes(&type, sizeof(type));

    uint8_t id = update->getId();
    sendBytes(&id, sizeof(id));

    uint8_t returnCode = update->getReturnCode();
    sendBytes(&returnCode, sizeof(returnCode));

    uint8_t numberOfGames = update->getNumberOfGames();
    sendBytes(&numberOfGames, sizeof(numberOfGames));

    std::vector<uint8_t> returnData = update->getListData();
    sendBytes(returnData.data(), returnData.size());
}
void
ServerProtocolo::serializeWorldUpdate(ServerUpdateWorld *update, std::function<void(void *, unsigned int)> &sendBytes) {
    std::vector<int> matchInfo = update->getInfo();
    //  Ball
    uint16_t ballX = (uint16_t) htons(matchInfo[0]);
    uint16_t ballY = (uint16_t) htons(matchInfo[1]);
    sendBytes(&ballX, sizeof(ballX));
    sendBytes(&ballY, sizeof(ballY));

    //  Score
    uint16_t local = (uint16_t) htons(matchInfo[2]);
    uint16_t visit = (uint16_t) htons(matchInfo[3]);
    sendBytes(&local, sizeof(local));
    sendBytes(&visit, sizeof(visit));

    //  Tiempo restante
    uint16_t time = (uint16_t) htons(matchInfo[5]);
    sendBytes(&time, sizeof(time));

    //  Numero de Clientes
    uint16_t n_clients = (uint16_t) htons(matchInfo[4]);
    sendBytes(&n_clients, sizeof(n_clients));

    int vSize = matchInfo.size();

    //  Clientes
    for (int i = INITIAL_POSITION ; i < vSize; i += 6) {

        uint16_t id = (uint16_t) htons(matchInfo[i]);
        sendBytes(&id, sizeof(id));

        uint16_t x = (uint16_t) htons(matchInfo[i + 1]);
        sendBytes(&x, sizeof(x));

        uint16_t y = (uint16_t) htons(matchInfo[i + 2]);
        sendBytes(&y, sizeof(y));

        uint16_t sign = (uint16_t) htons(matchInfo[i + 3]);
        sendBytes(&sign, sizeof(sign));

        uint32_t angle = (uint32_t) htonl(matchInfo[i + 4]);
        sendBytes(&angle, sizeof(angle));

        uint16_t facing = (uint16_t) htons(matchInfo[i + 5]);
        sendBytes(&facing, sizeof(facing));
    }

}

void
ServerProtocolo::serializeStatsUpdate(ServerUpdateStats *updateStats, std::function<void(void *, unsigned int)> &sendBytes) {
    std::vector<int> stats = updateStats->getStats();
    uint8_t players = stats[0];
    sendBytes(&players, sizeof(players));

    for (int i = 1; i < (stats.size()); i+=2) {
        uint8_t id = stats[i];
        std::cout << "id: " << (int)id << std::endl;
        uint8_t goals = stats[i+1];
        std::cout << "goals: " << (int)goals << std::endl;
        sendBytes(&id, sizeof(id));
        sendBytes(&goals, sizeof(goals));
    }
}

std::shared_ptr<ServerAction>
        ServerProtocolo::deserializeDataOnCommand(uint8_t &actionType, uint8_t &id, GameManager &gameManager,
                                                  std::function<void(void *, int)> &receiveBytes,
                                                  std::function<void(void *, unsigned int)> &sendBytes,
                                                  std::function<void(ProtectedQueue<std::shared_ptr<ServerAction>> *,
                                                                     BlockingQueue<std::optional<std::shared_ptr<ServerUpdate>>> *)> &startThreadsCallable) {
    switch (actionType) {
        case CREATE_ROOM:
            return parseCreateAction(id, receiveBytes, gameManager);
        case JOIN_ROOM:
            return parseJoinAction(id, receiveBytes, gameManager);
        case LIST_ROOMS:
            return parseListAction(id, gameManager);
    }
    return {};
}

std::shared_ptr<ServerAction>
        ServerProtocolo::parseCreateAction(uint8_t &id, const std::function<void(void *, int)>& receiveBytes,
                                           GameManager &gameManager) {
    std::vector<uint8_t> capacity_and_nameSize(2);
    receiveBytes(capacity_and_nameSize.data(), capacity_and_nameSize.size());
    uint8_t capacity = capacity_and_nameSize[0];
    uint8_t nameSize = capacity_and_nameSize[1];

    std::vector<uint8_t> name(nameSize);
    receiveBytes(name.data(), name.size());
    std::string nameString(name.begin(), name.end());

    std::shared_ptr<ServerAction> pAction = std::make_shared<ServerCreateRoom>(id, capacity, nameString, gameManager);
    return pAction;
}

std::shared_ptr<ServerAction>
        ServerProtocolo::parseJoinAction(const uint8_t &id, const std::function<void(void *, int)> &receiveBytes,
                                         GameManager &gameManager) {
    std::vector<uint8_t> nameSize(1);
    receiveBytes(nameSize.data(), nameSize.size());

    std::vector<uint8_t> name(nameSize[0]);
    receiveBytes(name.data(), name.size());
    std::string nameString(name.begin(), name.end());

    std::shared_ptr<ServerAction> pAction = std::make_shared<ServerJoinRoom>(id, nameString, gameManager);
    return pAction;
}

std::shared_ptr<ServerAction> ServerProtocolo::parseListAction(const uint8_t &id, GameManager &gameManager) {
    std::shared_ptr<ServerAction> pAction = std::make_shared<ServerListRooms>(id, gameManager);
    return pAction;
}
