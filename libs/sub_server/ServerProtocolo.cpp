//
// Created by lucaswaisten on 04/11/22.
//

#include <iostream>
#include "ServerProtocolo.h"

command_t Protocolo::getMapCommand(uint32_t action) {
    return this->mapCommand.at(action);
}

std::shared_ptr<ServerAction> Protocolo::deserializeData(const uint8_t &id, const uint8_t &type,
                                                         const std::function<void(std::vector<uint8_t> &, uint8_t &)> &receiveBytes) {
    switch (type) {
        case CREATE_ROOM:
            return parseCreateAction(id, receiveBytes);
        case JOIN_ROOM:
            return parseJoinAction(id, receiveBytes);
        case LIST_ROOMS:
            return parseListAction(id);
        case MOVE:
            return parseUpdateAction();
    }
    return {};
}

std::shared_ptr<ServerAction>
Protocolo::parseCreateAction(const uint8_t &id, const std::function<void(std::vector<uint8_t> &, uint8_t &)> &receiveBytes) {

    std::vector<uint8_t> capacity_and_nameSize(2);
    uint8_t size = capacity_and_nameSize.size();
    receiveBytes(capacity_and_nameSize, size);
    uint8_t capacity = capacity_and_nameSize[0];
    uint8_t nameSize = capacity_and_nameSize[1];

    std::vector<uint8_t> name(nameSize);
    size = name.size();
    receiveBytes(name, size);
    std::string nameString(name.begin(), name.end());

    std::shared_ptr<ServerAction> pAction = std::make_shared<ServerCreateRoom>(id, capacity, nameString);
    return pAction;
}

std::shared_ptr<ServerAction> Protocolo::parseJoinAction(const uint8_t &id, const std::function<void(std::vector<uint8_t> &,
                                                                                                     uint8_t &)> &receiveBytes) {
    std::vector<uint8_t> nameSize(1);
    uint8_t size = nameSize.size();
    receiveBytes(nameSize, size);

    std::vector<uint8_t> name(nameSize[0]);
    size = name.size();
    receiveBytes(name, size);
    std::string nameString(name.begin(), name.end());

    std::shared_ptr<ServerAction> pAction = std::make_shared<ServerJoinRoom>(id, nameString);
    return pAction;
}

std::shared_ptr<ServerAction> Protocolo::parseListAction(const uint8_t &id) {
    std::shared_ptr<ServerAction> pAction = std::make_shared<ServerListRooms>(id);
    return pAction;
}

void Protocolo::serializeUpdate(std::shared_ptr<ServerUpdate> update) {
    update->beSerialized(this);
}

void Protocolo::serializeCreateACK(ServerCreateACK *update) {
    uint8_t id = update->getId();
    sendBytes(&id, sizeof(id));

    uint8_t returnCode = update->getReturnCode();
    sendBytes(&returnCode, sizeof(returnCode));
}

void Protocolo::serializeJoinACK(ServerJoinACK *update) {
    uint8_t id = update->getId();
    sendBytes(&id, sizeof(id));

    uint8_t returnCode = update->getReturnCode();
    sendBytes(&returnCode, sizeof(returnCode));
}

void Protocolo::serializeServerListACK(ServerListACK *update) {
    uint8_t id = update->getId();
    sendBytes(&id, sizeof(id));

    uint8_t returnCode = update->getReturnCode();
    sendBytes(&returnCode, sizeof(returnCode));
//    //[id,returnCode, cantidadDeGames,{online,max,sieName,name},...]

    uint8_t numberOfGames = update->getNumberOfGames();
    sendBytes(&numberOfGames, sizeof(numberOfGames));

    // vector of uint8_t from first 3 items of returnData
    std::vector<uint8_t> returnData = update->getReturnData();
    std::vector<uint8_t> returnDataFirst3(returnData.begin(), returnData.begin() + 3);
    sendBytes(returnDataFirst3.data(), returnDataFirst3.size());

    // send the rest of returnData
    std::vector<uint8_t> returnDataRest(returnData.begin() + 3, returnData.end());
    sendBytes(returnDataRest.data(), returnDataRest.size());

    uint16_t test = htons(3122);
    sendBytes(&test, sizeof(test));
}

void Protocolo::serializeWorldUpdate(ServerUpdateWorld *update) {
    //implement
    std::vector<int> matchInfo = update->getInfo();
    //  Ball
    uint16_t ballX = (uint16_t) matchInfo[0];
    uint16_t ballY = (uint16_t) matchInfo[1];
    sendBytes(&ballX, sizeof(ballX));
    sendBytes(&ballY, sizeof(ballY));

    //  Score
    uint16_t local = (uint16_t) matchInfo[2];
    uint16_t visit = (uint16_t) matchInfo[3];
    sendBytes(&local, sizeof(local));
    sendBytes(&visit, sizeof(visit));

    //  Numero de Clientes
    uint16_t n_clients = (uint16_t) matchInfo[4];
    sendBytes(&n_clients, sizeof(n_clients));

    int vSize = matchInfo.size();

    //  Clientes
    for (int i = 5; i<vSize; i++) {
        uint16_t carInfo = (uint16_t) matchInfo[i];
        sendBytes(&carInfo, sizeof(carInfo));
    }

}
// TODO: IMPLEMENT
std::unique_ptr<ServerAction> Protocolo::parseUpdateAction() {
    return nullptr;
}
