//
// Created by lucaswaisten on 05/12/22.
//

#ifndef ROCKETLEAGUE_MOCKACKPROTOCOL_H
#define ROCKETLEAGUE_MOCKACKPROTOCOL_H


class MockACKProtocol {
public:
    MockACKProtocol(uint8_t id, uint8_t returnCode) {
        data.push(id);
        data.push(returnCode);
    }
    MockACKProtocol(const std::vector<uint8_t>& dataRecive,std::string string) {
        for ( auto & iter  : dataRecive){
            data.push(iter);
        }
        for(auto & i : string){
            data.push(i);
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


#endif //ROCKETLEAGUE_MOCKACKPROTOCOL_H
