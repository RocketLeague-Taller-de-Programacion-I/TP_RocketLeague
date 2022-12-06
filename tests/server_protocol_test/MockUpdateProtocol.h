//
// Created by lucaswaisten on 05/12/22.
//

#ifndef ROCKETLEAGUE_MOCKUPDATEPROTOCOL_H
#define ROCKETLEAGUE_MOCKUPDATEPROTOCOL_H


class MockUpdateProtocol {
public:

    MockUpdateProtocol() = default;

    void sendBytes(void *bytes_to_read, int size) {
        auto * pbytes_to_read = (uint8_t *) bytes_to_read;
        for(unsigned int i=0; i < size;i++){
            data.push(*pbytes_to_read);
            if (size > 1)  *pbytes_to_read++ ;
        }
    }
    uint8_t getType(){
        uint8_t type = data.front();
        data.pop();
        return type;
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

private:
    std::queue<uint8_t> data;
};


#endif //ROCKETLEAGUE_MOCKUPDATEPROTOCOL_H
