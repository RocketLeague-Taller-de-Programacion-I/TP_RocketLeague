#ifndef ROCKETLEAGUE_MOCKSERVERPROTOCOL_H
#define ROCKETLEAGUE_MOCKSERVERPROTOCOL_H

#include <cstdint>
#include <vector>
#include <string>
#include <netinet/in.h>
#include <queue>

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

    void receiveBytes(std::vector<uint8_t> &bytes_to_read, uint8_t &size) {
        for (int i =0 ; i<size;i++) {
             bytes_to_read[i] = (data.front()) ;
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
    uint8_t getId() {
        uint8_t id = data.front();
        data.pop();
        return id;
    }
    uint8_t getRetunCode() {
        uint8_t code = data.front();
        data.pop();
        return code;
    }

    uint8_t ballPosition() {
        uint8_t code = data.front();
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
    std::queue<uint16_t> dataWorld;
};
#endif //ROCKETLEAGUE_MOCKSERVERPROTOCOL_H
