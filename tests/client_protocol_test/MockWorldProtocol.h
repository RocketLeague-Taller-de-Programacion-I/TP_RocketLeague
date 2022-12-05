//
// Created by lucaswaisten on 05/12/22.
//

#ifndef ROCKETLEAGUE_MOCKWORLDPROTOCOL_H
#define ROCKETLEAGUE_MOCKWORLDPROTOCOL_H


#include <cstdint>
#include <vector>
#include <queue>
#include <netinet/in.h>

class MockWorldProtocol {
public:
    explicit MockWorldProtocol(const std::vector<uint16_t>& dataRecive) {
        for ( auto & iter  : dataRecive){
            data.push( htons(iter));
        }
    }
    void receiveBytes(void *bytes_to_read, int size) {
        auto * pbytes_to_read = (uint16_t *) bytes_to_read;
        *pbytes_to_read = data.front() ;
        data.pop();
    }

private:
    std::queue<uint16_t> data;
};


#endif //ROCKETLEAGUE_MOCKWORLDPROTOCOL_H
