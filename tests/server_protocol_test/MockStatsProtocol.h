//
// Created by lucaswaisten on 06/12/22.
//

#ifndef ROCKETLEAGUE_MOCKSTATSPROTOCOL_H
#define ROCKETLEAGUE_MOCKSTATSPROTOCOL_H


class MockStatsProtocol {

public:
    void sendBytesStatsMock(void *bytes_to_read, unsigned int size) {
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
    uint8_t getCantPlayer() {
        uint8_t cantPlayer = data.front();
        data.pop();
        return cantPlayer;
    }
    uint8_t getScore() {
        uint8_t score = data.front();
        data.pop();
        return score;
    }
private:
    std::queue<uint8_t> data;
};


#endif //ROCKETLEAGUE_MOCKSTATSPROTOCOL_H
