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
    explicit MockWorldProtocol(const std::vector<uint16_t>& dataRecive) :isBall(false) {
        for (int i = 0;i<dataRecive.size();i++){
            if( i == 3 )
                angle_ball = htonl(dataRecive[i]);
            else if(i==12){
                angle = htonl(dataRecive[i]);
            }
            else
                data.push( htons(dataRecive[i]));
        }
    }
    void receiveBytes(void *bytes_to_read, int size) {
        if(size == 4) {
            auto * pbytes_to_read = (uint32_t *) bytes_to_read;
            if(!isBall) {
                *pbytes_to_read = angle_ball;
                isBall = true;
                return;
            }
             *pbytes_to_read = angle ;
            return;
        }
        auto * pbytes_to_read = (uint16_t *) bytes_to_read;
        *pbytes_to_read = data.front() ;
        data.pop();
    }

private:
    uint32_t angle;
    std::queue<uint16_t> data;
    uint32_t angle_ball;
    bool isBall ;
};


#endif //ROCKETLEAGUE_MOCKWORLDPROTOCOL_H
