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
        case GAME_OVER:
            return parseStatsUpdate(receiveBytes);
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

    uint8_t cantGames;
    receiveBytes(&cantGames, sizeof(cantGames));

    std::map<std::string,std::string> games;
    //[id,returnCode, cantidadDeGames,{online,max,sizeName,name},...]

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

    std::shared_ptr<ClientUpdate> update = std::make_shared<ClientListACK>(id, returnCode, games);
    return update;
}

std::shared_ptr<ClientUpdate> ClientProtocol::parseWorldUpdate(const std::function<void(void *, int)> &receiveBytes) {
    uint16_t ballX;
    float ballXFloat;
    receiveBytes(&ballX, sizeof(ballX));
    ballX = ntohs(ballX);
    ballXFloat = ballX/1000.0;

    uint16_t ballY;
    float ballYFloat;
    receiveBytes(&ballY, sizeof(ballY));
    ballY = ntohs(ballY);
    ballYFloat = ballY/1000.0;
    Ball ball(ballXFloat, ballYFloat);

    //  Score
    uint16_t local;
    receiveBytes(&local, sizeof(local));
    local = ntohs(local);
    uint16_t visit;
    receiveBytes(&visit, sizeof(visit));
    visit = ntohs(visit);
    Score score(local, visit);

    // Time
    uint16_t time;
    receiveBytes(&time, sizeof(time));
    time = ntohs(time);
    GameTime gameTime(time);

    //  n_clients
    uint16_t n_clients;
    receiveBytes(&n_clients, sizeof(n_clients));
    n_clients = ntohs(n_clients);

    std::vector<Car> clientCars;
    //  CLients
    for (unsigned int i = 0; i < n_clients; i++) {
        uint16_t id;
        receiveBytes(&id, sizeof(id));
        id = ntohs(id);

        uint16_t x;
        receiveBytes(&x, sizeof(x));
        x = ntohs(x);
        float xFloat = float(x);
        xFloat = xFloat/1000.0;

        uint16_t y;
        receiveBytes(&y, sizeof(y));
        y = ntohs(y);
        float yFloat = float(y);
        yFloat = y/1000.0;

        uint16_t angleSign;
        receiveBytes(&angleSign, sizeof(angleSign));
        angleSign = ntohs(angleSign);

        uint32_t angle; //uint32_t
        receiveBytes(&angle, sizeof(angle));
        angle = ntohl(angle);
        float angleFloat = float(angle);
        angleFloat = angleFloat / 1000.0 *  (angleSign ? 1 : -1);

        uint16_t facingWhere;  // 0 right, 1 left
        receiveBytes(&facingWhere, sizeof(facingWhere));
        facingWhere = ntohs(facingWhere);

        Car car(id, xFloat, yFloat, angleFloat, facingWhere);
        clientCars.emplace_back(car);
    }

    std::shared_ptr<ClientUpdate> update = std::make_shared<ClientUpdateWorld>(ball, score, gameTime, clientCars);
    return update;
}

std::shared_ptr<ClientUpdate> ClientProtocol::parseStatsUpdate(const std::function<void(void *, int)> &receiveBytes) {
    uint8_t numberOfPlayers;
    receiveBytes(&numberOfPlayers, sizeof(numberOfPlayers));

    std::map<uint8_t, uint8_t> stats;
    for (int i = 0; i < numberOfPlayers; i++) {
        uint8_t id;
        receiveBytes(&id, sizeof(id));

        if(!id) continue; // 0 is not a valid id

        uint8_t score;
        receiveBytes(&score, sizeof(score));
        stats[id] = score;
    }

    std::shared_ptr<ClientUpdate> update = std::make_shared<ClientUpdateStats>(stats);
    return update;
}

void ClientProtocol::serializeAction(std::shared_ptr<ClientAction> action) {
    action->beSerialized(this);
}

void ClientProtocol::serializeCreateRoom(ActionCreateRoom *action) {
    std::vector<uint8_t> capacity_and_nameSize(2);
    capacity_and_nameSize[0] = action->getCapacity();
    capacity_and_nameSize[1] = action->getGameName().size();
    sendBytes(capacity_and_nameSize.data(), capacity_and_nameSize.size());

    std::string name = action->getGameName();
    std::vector<uint8_t> nameVector(name.begin(), name.end());

    sendBytes(nameVector.data(), (nameVector.size()));
}

void ClientProtocol::serializeJoinRoom(ActionJoinRoom *action) {
    uint8_t nameSize = action->getRoomName().size();
    sendBytes(&nameSize, sizeof(nameSize));

    std::string name = action->getRoomName();
    std::vector<uint8_t> nameVector(name.begin(), name.end());
    sendBytes(nameVector.data(), (nameVector.size()));
}

void ClientProtocol::serializeListRooms(ActionListRooms *action) {
    // Only send the type of action
}

void ClientProtocol::serializeMove(ClientActionMove *action) {
    uint8_t id = action->getIdPlayer();
    sendBytes(&id, sizeof(id));

    uint8_t direction = action->getDirection();
    sendBytes(&direction, sizeof(direction));

    uint8_t state = action->getState();
    sendBytes(&state, sizeof(state));
}
