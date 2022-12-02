//
// Created by lucaswaisten on 29/11/22.
//

#ifndef ROCKETLEAGUE_MOCKSERVERPROTOCOL_H
#define ROCKETLEAGUE_MOCKSERVERPROTOCOL_H

#include <cstdint>
#include <vector>
#include <string>
#include <netinet/in.h>
#include <queue>

class MockServerProtocol {
public:
    MockServerProtocol(uint8_t id, uint8_t returnCode) {
        data.push(id);
        data.push(returnCode);
    }

    MockServerProtocol(const std::vector<uint8_t>& dataRecive,std::string string) {
        for ( auto & iter  : dataRecive){
            data.push(iter);
        }
        for(auto & i : string){
            data.push(i);
        }
    }
    MockServerProtocol(const std::vector<uint16_t>& dataRecive) {
        for ( auto & iter  : dataRecive){
            dataWorld.push( htons(iter));
        }
    }

    void receiveBytes(std::vector<uint8_t> &bytes_to_read, uint8_t &size) {
       /* for (int i =0 ; i<size;i++) {
            bytes_to_read = data.front() ;
            if (size > 1)  bytes_to_read++ ;
            data.pop();
        }*/
    }
    void receiveBytesWorld(void *bytes_to_read, int size) {
        auto * pbytes_to_read = (uint16_t *) bytes_to_read;
        *pbytes_to_read = dataWorld.front() ;
        dataWorld.pop();
    }
private:
    std::queue<uint8_t> data;
    std::queue<uint16_t> dataWorld;
};
#endif //ROCKETLEAGUE_MOCKSERVERPROTOCOL_H
