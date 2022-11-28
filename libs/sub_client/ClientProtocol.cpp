//
// Created by roby on 22/11/22.
//

#include <netinet/in.h>
#include "ClientProtocol.h"

ClientUpdate *ClientProtocol::deserializeData(const uint8_t &type, const std::function<void(void *, int)> &receiveBytes) {
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
//        case WORLD:
//            return parseWorldUpdate(receiveBytes);
    }
    return nullptr;
}

ClientUpdate *ClientProtocol::parseCreateACK(
        const std::function<void(void *, int)> &receiveBytes) {

    uint8_t id;
    receiveBytes(&id, sizeof(id));

    uint8_t returnCode;
    receiveBytes(&returnCode, sizeof(returnCode));

    return new ClientCreateACK(id, returnCode);
    //CreateACK -> CreateACK(id,returnCode) returnCode = 1 OK, 2 ERROR_Existe
}

ClientUpdate *ClientProtocol::deserializeCreateACK(const std::vector<uint16_t> &data) {
    uint16_t id = data[1];
    uint16_t returnCode = data[2];
    return new ClientCreateACK(reinterpret_cast<uint8_t &>(id), reinterpret_cast<uint8_t &>(returnCode));
    //CreateACK -> CreateACK(id,returnCode) returnCode = 1 OK, 2 ERROR_Existe
}

ClientUpdate *ClientProtocol::parseJoinACK(const std::function<void(void *, int)> &receiveBytes) {
    uint8_t id;
    receiveBytes(&id, sizeof(id));

    uint8_t returnCode;
    receiveBytes(&returnCode, sizeof(returnCode));


    return new ClientJoinACK(id, returnCode);
    //JoinAck -> JoinAck(id,returnCode) returnCode = 1 OK, 2 ERROR_LLENO
}

ClientUpdate *ClientProtocol::parseListUpdate(
        const std::function<void(void *, int)> &receiveBytes) {
    uint8_t id;
    receiveBytes(&id, sizeof(id));

    uint8_t returnCode;
    receiveBytes(&returnCode, sizeof(returnCode));


    if (returnCode == ERROR_FULL) {
        std::map<std::string,std::string> games;
        return new ClientListACK(id, returnCode, games);
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

    return new ClientListACK(id, returnCode, games);
    //ListInfo -> ListInfo(id,lista)
}

// TODO: implement this
ClientUpdate *ClientProtocol::parseWorldUpdate(const std::vector<uint8_t> &vector) {
    return nullptr;
}

ClientUpdate *ClientProtocol::parseStartedGameACK(const std::function<void(std::vector<uint8_t> &, uint8_t &)> &function) {
    std::vector<uint8_t> id_and_returncode(2);
    uint8_t size = id_and_returncode.size();
    function(id_and_returncode, size);

    return new ClientStartedGameACK(id_and_returncode[0], id_and_returncode[1]);
}
