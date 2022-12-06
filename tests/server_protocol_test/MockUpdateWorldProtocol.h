//
// Created by lucaswaisten on 05/12/22.
//

#ifndef ROCKETLEAGUE_MOCKUPDATEWORLDPROTOCOL_H
#define ROCKETLEAGUE_MOCKUPDATEWORLDPROTOCOL_H


#include <cstdint>
#include <queue>
#include <netinet/in.h>

class MockUpdateWorldProtocol {
public:
    MockUpdateWorldProtocol() = default;

    void sendBytes(void *bytes_to_read, int size) {
        auto * pbytes_to_read = (uint16_t *) bytes_to_read;
        auto i = htons((*pbytes_to_read));
        data.push(i);
    }

    uint16_t getTime() {
        uint8_t code = data.front();
        data.pop();
        return code;
    }
    uint16_t ballPosition() {
        uint16_t code = data.front();
        data.pop();
        return code;
    }

    int getScoreLocal() {
        uint8_t code = data.front();
        data.pop();
        return code;
    }
    int getScoreVisitor() {
        uint8_t code = data.front();
        data.pop();
        return code;
    }
private:
    std::queue<uint8_t> data;
};


#endif //ROCKETLEAGUE_MOCKUPDATEWORLDPROTOCOL_H
