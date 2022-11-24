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
    std::string returnData; // TODO: cambiar a vector?
public:
    ServerUpdate(uint8_t &id, std::string &returnData) : id(id), returnData(returnData) {};
    virtual ~ServerUpdate() = default;

    virtual std::uint8_t getType() const = 0;
    virtual std::string getReturnData() const { return returnData; };
    virtual std::vector<uint8_t> beSerialized() = 0;
};


#endif //ROCKETLEAGUE_SERVERUPDATE_H
