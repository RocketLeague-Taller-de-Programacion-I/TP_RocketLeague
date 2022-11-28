//
// Created by roby on 22/11/22.
//

#include "ClientProtocol.h"

ClientUpdate *ClientProtocol::deserializeData(const uint8_t &type, const std::function<void(std::vector<uint8_t>&, uint8_t&)> &receiveBytes) {
    //type is sent as first byte (by server)
    switch (type) {
        case CREATE_ACK:
            return parseCreateACK(receiveBytes);
        case JOIN_ACK:
            return parseJoinACK(receiveBytes);
        case LIST_INFO:
            return parseListUpdate(receiveBytes);
        case STARTED_GAME_ACK:
            return parseStartedGameACK(receiveBytes);
        case WORLD:
            return parseWorldUpdate(receiveBytes);
        }
    return nullptr;
}

ClientUpdate *ClientProtocol::parseCreateACK(const std::function<void(std::vector<uint8_t> &, uint8_t &)> &receiveBytes) {

    std::vector<uint8_t> id_and_returncode(2);
    uint8_t size = id_and_returncode.size();
    receiveBytes(id_and_returncode, size);

    return new ClientCreateACK(id_and_returncode[0], id_and_returncode[1]);
    //CreateACK -> CreateACK(id,returnCode) returnCode = 1 OK, 2 ERROR_Existe
}

ClientUpdate *ClientProtocol::deserializeCreateACK(const std::vector<uint8_t> &data) {
    uint8_t id = data[1];
    uint8_t returnCode = data[2];
    return new ClientCreateACK(id, returnCode);
    //CreateACK -> CreateACK(id,returnCode) returnCode = 1 OK, 2 ERROR_Existe
}

ClientUpdate *ClientProtocol::parseJoinACK(const std::function<void(std::vector<uint8_t> &, uint8_t &)> &receiveBytes) {
    std::vector<uint8_t> id_and_returncode(2);
    uint8_t size = id_and_returncode.size();
    receiveBytes(id_and_returncode, size);

    return new ClientJoinACK(id_and_returncode[0], id_and_returncode[1]);
    //JoinAck -> JoinAck(id,returnCode) returnCode = 1 OK, 2 ERROR_LLENO
}

ClientUpdate *ClientProtocol::parseListUpdate(const std::function<void(std::vector<uint8_t> &, uint8_t &)> &receiveBytes) {
    std::vector<uint8_t> id_and_returncode(2);
    uint8_t size = id_and_returncode.size();
    receiveBytes(id_and_returncode, size);

    if (id_and_returncode[1] == ERROR_FULL) {
        std::map<std::string,std::string> games;
        return new ClientListACK(id_and_returncode[0],id_and_returncode[1], games);
    }

    std::vector<uint8_t> cantGames(1);
    size = cantGames.size();
    receiveBytes(cantGames, size);

    std::map<std::string,std::string> games;
    //[id,returnCode, cantidadDeGames,{online,max,sieName,name},...]

    for(uint8_t cant = cantGames[0], i = 0; i < cant; i++) {
        std::vector<uint8_t> players_and_size(3);
        size = players_and_size.size();
        receiveBytes(players_and_size, size);

        uint8_t playersOnLine = players_and_size[0];
        uint8_t capacity = players_and_size[1];
        uint8_t nameSize = players_and_size[2];

        std::vector<uint8_t> name(nameSize);
        size = name.size();
        receiveBytes(name, size);

        std::string gameName = std::string(name.begin(), name.end());

        games[gameName] = std::to_string(playersOnLine) + "/" + std::to_string(capacity);
    }

    return new ClientListACK(id_and_returncode[0],id_and_returncode[1], games);
    //ListInfo -> ListInfo(id,lista)
}

ClientUpdate *ClientProtocol::parseStartedGameACK(const std::function<void(std::vector<uint8_t> &, uint8_t &)> &receiveBytes) {
    std::vector<uint8_t> id_and_returncode(2);
    uint8_t size = id_and_returncode.size();
    receiveBytes(id_and_returncode, size);

    return new ClientStartedGameACK(id_and_returncode[0], id_and_returncode[1]);
}

ClientUpdate *ClientProtocol::parseWorldUpdate(
        const std::function<void(std::vector<uint8_t> &, uint8_t &)> &receiveBytes) {
//    bola -> 4bytes
    std::vector<uint8_t> ball_x_and_y(4);
    uint8_t size = ball_x_and_y.size();
    receiveBytes(ball_x_and_y, size);

    uint16_t ball_x = (ball_x_and_y[0] << 8) | ball_x_and_y[1];
    uint16_t ball_y = (ball_x_and_y[2] << 8) | ball_x_and_y[3];
    Ball ball = Ball(ball_x, ball_y);

    //    score -> 2bytes
    std::vector<uint8_t> score(2);
    size = score.size();
    receiveBytes(score, size);

    uint8_t scoreLocal = score[0];
    uint8_t scoreVisit = score[1];
    Score scoreUpdate = Score(scoreLocal, scoreVisit);

//    numero de clientes 2 bytes //TODO: mandar 2 bytes
    std::vector<uint8_t> numberOfClient(1);
    size = numberOfClient.size();
    receiveBytes(numberOfClient, size);
//    cliente 7bytes
    std::vector<Car> cars;
    for(uint8_t i = 0; i < numberOfClient[0]; i++) {
        std::vector<uint8_t> client(8);
        size = client.size();
        receiveBytes(client, size);
        uint8_t id = client[0]; //-id 1byte
        uint16_t x = (client[1] << 8) | client[2]; //- x 2byte
        uint16_t y = (client[3] << 8) | client[4]; // - y 2byte
        uint8_t angleSign = client[5]; // - sign 1byte
        uint8_t angle = (client[5] << 8) | client[6]; //- angulo 2 bytes
        Car car = Car(id, x, y, angleSign, angle);
        cars.push_back(car);
    }

    ClientUpdate *update = new ClientUpdateWorld(ball, scoreUpdate, cars);
    return update;
}

