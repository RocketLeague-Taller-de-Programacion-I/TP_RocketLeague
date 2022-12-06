//
// Created by lucaswaisten on 05/12/22.
//

#ifndef ROCKETLEAGUE_MOCKACTIONPROTOCOL_H
#define ROCKETLEAGUE_MOCKACTIONPROTOCOL_H


#include <cstdint>
#include <queue>
#include <string>

class MockActionProtocol {
public:
    MockActionProtocol() = default;
    void sendBytes(void *bytes_to_read, int size) {
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
    uint8_t getId() {
        uint8_t id = data.front();
        data.pop();
        return id;
    }

    uint8_t getDirection() {
        uint8_t direction = data.front();
        data.pop();
        return direction;
    }

    bool getState() {
        bool direction = data.front();
        data.pop();
        return direction;
    }
private:
    std::queue<uint8_t> data;
};


#endif //ROCKETLEAGUE_MOCKACTIONPROTOCOL_H
