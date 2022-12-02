//
// Created by lucaswaisten on 29/11/22.
//

#ifndef ROCKETLEAGUE_MOCKCLIENTPROTOCOL_H
#define ROCKETLEAGUE_MOCKCLIENTPROTOCOL_H

#include <cstdint>
#include <string>
#include <queue>
#include <netinet/in.h>

class MockClientProtocol {
public:
    MockClientProtocol() = default;

    MockClientProtocol(uint8_t id, uint8_t returnCode) {
        data.push(id);
        data.push(returnCode);
    }

    MockClientProtocol(const std::vector<uint8_t>& dataRecive,std::string string) {
        for ( auto & iter  : dataRecive){
            data.push(iter);
        }
        for(auto & i : string){
            data.push(i);
        }
    }
    explicit MockClientProtocol(const std::vector<uint16_t>& dataRecive) {
        for ( auto & iter  : dataRecive){
            dataWorld.push( htons(iter));
        }
    }

    void receiveBytes(void *bytes_to_read, int size) {
        auto * pbytes_to_read = (uint8_t *) bytes_to_read;
        for (int i =0 ; i<size;i++) {
            *pbytes_to_read = data.front() ;
            if (size > 1)  *pbytes_to_read++ ;
            data.pop();
        }
    }
    void receiveBytesWorld(void *bytes_to_read, int size) {
        auto * pbytes_to_read = (uint16_t *) bytes_to_read;
        *pbytes_to_read = dataWorld.front() ;
        dataWorld.pop();
    }

    void sendBytesMock(void *bytes_to_read, int size) {
        auto * pbytes_to_read = (uint8_t *) bytes_to_read;
        for(unsigned int i=0; i < size;i++){
            data.push(*pbytes_to_read);
            if (size > 1)  *pbytes_to_read++ ;
        }
    }

    int getCapacity() {
        auto c = data.front();
        data.pop();
        return c;
    }
    int getSizeName() {
        auto size = data.front();
        data.pop();
        return size;
    }
    std::string getName(int size){
        std::string name;
        for(int i = 0; i<size;i++){
            name.push_back(data.front());
            data.pop();
        }
        return name;
    }

private:
    std::queue<uint8_t> data;
    std::queue<uint16_t> dataWorld;
};
#endif //ROCKETLEAGUE_MOCKCLIENTPROTOCOL_H
