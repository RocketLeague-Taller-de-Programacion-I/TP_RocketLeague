//
// Created by lucaswaisten on 29/11/22.
//

#ifndef ROCKETLEAGUE_MOCKCLIENTPROTOCOL_H
#define ROCKETLEAGUE_MOCKCLIENTPROTOCOL_H

#include <cstdint>
#include <string>
#include <queue>

class MockClientProtocol {
public:
    MockClientProtocol(uint8_t id, uint8_t returnCode) {
        data.push(id);
        data.push(returnCode);
    }

    MockClientProtocol(uint8_t id, uint8_t returnCode, uint8_t cantGame, uint8_t online, uint8_t capacity,
                       uint8_t sizeName, const std::string &name) {
        data.push(id);
        data.push(returnCode);
        data.push(cantGame);
        data.push(online);
        data.push(capacity);
        data.push(sizeName);
        for(auto & i : name){
            data.push(i);
        }
    }

    MockClientProtocol(uint8_t i, uint8_t i1, uint8_t i2, uint8_t i3, uint8_t i4, uint8_t i5, uint8_t i6, uint8_t i7, uint8_t i8, uint8_t i9) {

    }

    MockClientProtocol(std::vector<uint8_t> dataRecive,std::string string) {
        for ( auto & iter  : dataRecive){
            data.push(iter);
        }
        for(auto & i : string){
            data.push(i);
        }
    }

    void receiveBytes(void *bytes_to_read, int size) {
        auto * pbytes_to_read = (uint8_t *) bytes_to_read;
        for (int i =0 ; i<size;i++){
            *pbytes_to_read = data.front() ;
            if (size > 1)  *pbytes_to_read++ ;
            data.pop();
        }

    }
private:
    std::queue<uint8_t> data;
};
#endif //ROCKETLEAGUE_MOCKCLIENTPROTOCOL_H
