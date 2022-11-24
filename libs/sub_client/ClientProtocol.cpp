//
// Created by roby on 22/11/22.
//

#include "ClientProtocol.h"

GameUpdate *ClientProtocol::deserializeData(const std::vector<uint8_t> &data) {
    //type is sent as first byte (by server)
    uint8_t type = data[0];
    switch (type) {
        case CREATE_ACK:
            return parseCreateACK(data);
        case JOIN_ACK:
            return parseJoinACK(data);
        case LIST_INFO:
            return parseListUpdate(data);
        case WORLD:
            return parseWorldUpdate(data);
    }
    return nullptr;
}

GameUpdate *ClientProtocol::parseCreateACK(const std::vector<uint8_t> &data) {
    uint8_t id = data[1];
    std::string returnCode = std::string(data.begin() + 2, data.end());
    return new CreateACK(id, returnCode);
    //CreateACK -> CreateACK(id,returnCode) returnCode = 1 OK, 2 ERROR_Existe
}
GameUpdate *ClientProtocol::parseJoinACK(const std::vector<uint8_t> &data) {
    uint8_t id = data[1];
    std::string returnCode = std::string(data.begin() + 2, data.end());
    return new JoinACK(id, returnCode);
    //JoinAck -> JoinAck(id,returnCode) returnCode = 1 OK, 2 ERROR_LLENO
}

GameUpdate *ClientProtocol::parseListUpdate(const std::vector<uint8_t> &data) {
    uint8_t id = data[1];
    std::string list = std::string(data.begin() + 2, data.end());
    return new ListACK(id,list);
    //ListInfo -> ListInfo(id,lista)
}
// TODO: implement this
GameUpdate *ClientProtocol::parseWorldUpdate(const std::vector<uint8_t> &vector) {
    return nullptr;
}
