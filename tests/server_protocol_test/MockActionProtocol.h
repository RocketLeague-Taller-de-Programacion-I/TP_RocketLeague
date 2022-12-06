//
// Created by lucaswaisten on 05/12/22.
//

#ifndef ROCKETLEAGUE_MOCKACTIONPROTOCOL_H
#define ROCKETLEAGUE_MOCKACTIONPROTOCOL_H


class MockActionProtocol {
public:
    MockActionProtocol() = default;

    MockActionProtocol(uint8_t capacity, const std::string& nameRoom) {
        data.push(capacity);
        data.push((nameRoom.size()));
        for(auto & c : nameRoom){
            data.push((c));
        }
    }
    explicit MockActionProtocol(const std::string& nameRoom) {
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
private:
    std::queue<uint8_t> data;
};


#endif //ROCKETLEAGUE_MOCKACTIONPROTOCOL_H
