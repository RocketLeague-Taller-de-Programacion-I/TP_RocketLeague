//
// Created by roby on 22/11/22.
//

#include <netinet/in.h>
#include <memory>
#include "ClientProtocol.h"

std::shared_ptr<ClientUpdate> ClientProtocol::deserializeData(const uint8_t &type, const std::function<void(void *, int)> &receiveBytes) {
    //type is sent as first byte (by server)
    switch (type) {
        case CREATE_ACK:
            return parseCreateACK(receiveBytes);
         case JOIN_ACK:
            return parseJoinACK(receiveBytes);
        case LIST_INFO:
            return parseListUpdate(receiveBytes);
    // case STARTED_GAME_ACK:
       // return parseStartedGameACK(receiveBytes);
        case WORLD:
            return parseWorldUpdate(receiveBytes);
    }
    return nullptr;
}

std::shared_ptr<ClientUpdate> ClientProtocol::parseCreateACK(
        const std::function<void(void *, int)> &receiveBytes) {

    uint8_t id;
    receiveBytes(&id, sizeof(id));

    uint8_t returnCode;
    receiveBytes(&returnCode, sizeof(returnCode));

    std::shared_ptr<ClientUpdate> update = std::make_shared<ClientCreateACK>(id, returnCode);
    return update;
}

/*std::shared_ptr<ClientUpdate> ClientProtocol::deserializeCreateACK(const std::vector<uint16_t> &data) {
    uint16_t id = data[1];
    uint16_t returnCode = data[2];
    std::shared_ptr<ClientUpdate> update = std::make_shared<ClientCreateACK>(id, returnCode);
    return update;
    return new ClientCreateACK(reinterpret_cast<uint8_t &>(id), reinterpret_cast<uint8_t &>(returnCode));
    //CreateACK -> CreateACK(id,returnCode) returnCode = 1 OK, 2 ERROR_Existe
}*/

std::shared_ptr<ClientUpdate> ClientProtocol::parseJoinACK(const std::function<void(void *, int)> &receiveBytes) {
    uint8_t id;
    receiveBytes(&id, sizeof(id));

    uint8_t returnCode;
    receiveBytes(&returnCode, sizeof(returnCode));

    std::shared_ptr<ClientUpdate> update = std::make_shared<ClientJoinACK>(id, returnCode);
    return update;
}

std::shared_ptr<ClientUpdate> ClientProtocol::parseListUpdate(
        const std::function<void(void *, int)> &receiveBytes) {
    uint8_t id;
    receiveBytes(&id, sizeof(id));

    uint8_t returnCode;
    receiveBytes(&returnCode, sizeof(returnCode));


    if (returnCode == ERROR_FULL) {
        std::map<std::string,std::string> games;
        std::shared_ptr<ClientUpdate> update = std::make_shared<ClientListACK>(id, returnCode, games);
        return update;
    }

    uint8_t cantGames;
    receiveBytes(&cantGames, sizeof(cantGames));

    std::map<std::string,std::string> games;
    //[id,returnCode, cantidadDeGames,{online,max,sieName,name},...]

    for(uint8_t cant = cantGames, i = 0; i < cant; i++) {
        std::vector<uint8_t> players_and_size(3);
        receiveBytes(players_and_size.data(), 3);

        uint8_t playersOnLine = players_and_size[0];
        uint8_t capacity = players_and_size[1];
        uint8_t nameSize = players_and_size[2];

        std::vector<uint8_t> name(nameSize);
        receiveBytes(name.data(), name.size());

        std::string gameName = std::string(name.begin(), name.end());

        games[gameName] = std::to_string(playersOnLine) + "/" + std::to_string(capacity);
    }

    uint16_t test;
    receiveBytes(&test, sizeof(test));
    test = ntohs(test);

    std::shared_ptr<ClientUpdate> update = std::make_shared<ClientListACK>(id, returnCode, games);
    return update;
}

// TODO: implement this
std::shared_ptr<ClientUpdate> ClientProtocol::parseWorldUpdate(const std::function<void(void *, int)> &receiveBytes) {
    uint16_t ballX;
    receiveBytes(&ballX, sizeof(ballX));
    ballX = ntohs(ballX);
    uint16_t ballY;
    receiveBytes(&ballY, sizeof(ballY));
    ballY = ntohs(ballY);
    Ball ball(ballX, ballY);
    //  Score
    uint16_t local;
    receiveBytes(&local, sizeof(local));
    local = ntohs(local);
    uint16_t visit;
    receiveBytes(&visit, sizeof(visit));
    visit = ntohs(visit);
    Score score(local, visit);
    //  n_clients
    uint16_t n_clients;
    receiveBytes(&n_clients, sizeof(n_clients));
    n_clients = ntohs(n_clients);
    std::vector<Car> clientCars;
    //  CLients
    //  TODO: Vector de Cars
    for (unsigned int i = 0; i < n_clients; i++) {
        uint16_t id;
        receiveBytes(&id, sizeof(id));
        id = ntohs(id);
        uint16_t x;
        receiveBytes(&x, sizeof(x));
        x = ntohs(x);
        uint16_t y;
        receiveBytes(&y, sizeof(y));
        y = ntohs(y);
        uint16_t angleSign;
        receiveBytes(&angleSign, sizeof(angleSign));
        angleSign = ntohs(angleSign);
        uint16_t angle;
        receiveBytes(&angle, sizeof(angle));
        angle = ntohs(angle);
        Car car(id, x, y, angleSign, angle);
        clientCars.emplace_back(car);
    }

    std::shared_ptr<ClientUpdate> update = std::make_shared<ClientUpdateWorld>(ball, score, clientCars);
    return update;
}

std::shared_ptr<ClientUpdate>
ClientProtocol::parseStartedGameACK(const std::function<void(std::vector<uint8_t> &, uint8_t &)> &function) {
    std::vector<uint8_t> id_and_returncode(2);
    uint8_t size = id_and_returncode.size();
    function(id_and_returncode, size);

    std::shared_ptr<ClientUpdate> update = std::make_shared<ClientStartedGameACK>(id_and_returncode[0], id_and_returncode[1]);
    return update;
}
