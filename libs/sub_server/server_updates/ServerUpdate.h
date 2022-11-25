//
// Created by roby on 24/11/22.
//

#ifndef ROCKETLEAGUE_SERVERUPDATE_H
#define ROCKETLEAGUE_SERVERUPDATE_H


#include <cstdint>
#include <string>
#include <vector>

enum upodate_type { // TODO: cambiarles el nombre?
    CREATE_ACK = 1,
    JOIN_ACK = 2,
    LIST_INFO = 3,
    WORLD = 4
};

class ServerUpdate {
protected:
    uint8_t id;
    std::vector<uint8_t> returnData;
public:
    ServerUpdate(uint8_t &id, std::vector<uint8_t> &returnData) : id(id), returnData(returnData) {};
//    ServerUpdate(uint8_t &id, std::vector<uint8_t> &data) : id(id), data(data) {};
    virtual ~ServerUpdate() = default;

    virtual std::uint8_t getType() const = 0;
    virtual std::string getReturnData() const { return std::string(returnData.begin(), returnData.end()); }; //TODO> to change name or remove
    virtual std::vector<uint8_t> getData() const { return returnData; };
    virtual std::vector<uint8_t> beSerialized() = 0;
};


#endif //ROCKETLEAGUE_SERVERUPDATE_H
