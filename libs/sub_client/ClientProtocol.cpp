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
//        case WORLD:
//            return parseWorldUpdate(receiveBytes);
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


// TODO: implement this
ClientUpdate *ClientProtocol::parseWorldUpdate(const std::vector<uint8_t> &vector) {
    return nullptr;
}

void ClientProtocol::receiveBytes(std::vector<uint8_t> &data, uint8_t &size) {
    data.emplace_back(1);//id
    data.emplace_back(0);//returncode
}

ClientUpdate *ClientProtocol::parseStartedGameACK(const std::function<void(std::vector<uint8_t> &, uint8_t &)> &function) {
    std::vector<uint8_t> id_and_returncode(2);
    uint8_t size = id_and_returncode.size();
    receiveBytes(id_and_returncode, size);

    return new ClientStartedGameACK(id_and_returncode[0], id_and_returncode[1]);
}
