#ifndef ROCKETLEAGUE_MOCKSERVERPROTOCOL_H
#define ROCKETLEAGUE_MOCKSERVERPROTOCOL_H

#include <cstdint>
#include <vector>
#include <string>
#include <netinet/in.h>
#include <queue>
#include "sub_server/server_updates/ServerUpdate.h"

class MockServerProtocol {
public:

    MockServerProtocol() = default;

    MockServerProtocol(uint8_t capacity, const std::string& nameRoom) {
        data.push(capacity);
        data.push((nameRoom.size()));
        for(auto & c : nameRoom){
            data.push((c));
        }
    }

    explicit MockServerProtocol(const std::string& nameRoom) {
        data.push((nameRoom.size()));
        for(auto & c : nameRoom){
            data.push((c));
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
    void receiveDataMove(void *bytes_to_read, int size){
        auto * pbytes_to_read = (uint8_t *) bytes_to_read;
        *pbytes_to_read = data.front() ;
        data.pop();
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
    void sendBytesMockWorld(void *bytes_to_read, int size) {
        auto * pbytes_to_read = (uint16_t *) bytes_to_read;
        auto i = htons((*pbytes_to_read));
        dataWorld.push(i);
    }
    uint16_t getId() {
        uint16_t id = data.front();
        data.pop();
        return id;
    }
    uint16_t getRetunCode() {
        uint16_t code = data.front();
        data.pop();
        return code;
    }

    uint16_t ballPosition() {
        uint16_t code = dataWorld.front();
        dataWorld.pop();
        return code;
    }

    int getScoreLocal() {
        uint8_t code = dataWorld.front();
        dataWorld.pop();
        return code;
    }
    int getScoreVisitor() {
        uint8_t code = dataWorld.front();
        dataWorld.pop();
        return code;
    }

    uint8_t getType(){
        uint8_t type = data.front();
        data.pop();
        return type;
    }

    uint16_t getTime() {
        uint8_t code = dataWorld.front();
        dataWorld.pop();
        return code;
    }

private:
    std::queue<uint8_t> data;
    std::queue<uint16_t> dataWorld;
};
#endif //ROCKETLEAGUE_MOCKSERVERPROTOCOL_H
