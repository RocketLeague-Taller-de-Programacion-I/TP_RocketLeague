//
// Created by lucaswaisten on 05/12/22.
//

#ifndef ROCKETLEAGUE_MOCKMOVEPROTOCOL_H
#define ROCKETLEAGUE_MOCKMOVEPROTOCOL_H


#include <cstdint>
#include <queue>

class MockMoveProtocol {
public:
    MockMoveProtocol() = default;

    MockMoveProtocol(uint8_t id, uint8_t direction, uint8_t state) {
        data.push(id);
        data.push(direction);
        data.push(state);
    }

    void receiveData(void *bytes_to_read, int size){
        auto * pbytes_to_read = (uint8_t *) bytes_to_read;
        *pbytes_to_read = data.front() ;
        data.pop();
    }
private:
    std::queue<uint8_t> data;
    std::queue<uint16_t> dataWorld;
};



#endif //ROCKETLEAGUE_MOCKMOVEPROTOCOL_H
