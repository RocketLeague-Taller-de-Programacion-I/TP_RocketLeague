//
// Created by roby on 22/11/22.
//

#include "ClientProtocol.h"

GameUpdate *ClientProtocol::deserializeData(const std::vector<uint8_t> &data) {
    //type is sent as first byte (by server)
    uint8_t type = data[0];
    // id is sent as second byte (by server)
//    uint8_t id = data[1];
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
    std::vector<uint8_t> updateData;
    uint8_t id = data[1];
    uint8_t returnCode = data[2];
    updateData.push_back(id);
    updateData.push_back(returnCode);
    return new GameUpdate(updateData);
}
// TODO: maybe implement some parseAck to avoid code duplication
GameUpdate *ClientProtocol::parseJoinACK(const std::vector<uint8_t> &data) {
    std::vector<uint8_t> updateData;
    uint8_t id = data[1];
    uint8_t returnCode = data[2];
    updateData.push_back(id);
    updateData.push_back(returnCode);
    return new GameUpdate(updateData);
}

GameUpdate *ClientProtocol::parseListUpdate(const std::vector<uint8_t> &data) {
    std::vector<uint8_t> listData;
//    uint8_t id = data[1];
    std::string list = std::string(data.begin() + 2, data.end());
    listData.insert(listData.end(), list.begin(), list.end());
    return new GameUpdate(listData);
}
// TODO: implement this
GameUpdate *ClientProtocol::parseWorldUpdate(const std::vector<uint8_t> &vector) {
    return nullptr;
}
