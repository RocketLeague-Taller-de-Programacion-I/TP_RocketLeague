//
// Created by roby on 22/11/22.
//

#ifndef ROCKETLEAGUE_CLIENTUPDATE_H
#define ROCKETLEAGUE_CLIENTUPDATE_H

#include <vector>
#include <string>

enum updateType {
    CREATE_ACK = 1,
    JOIN_ACK = 2,
    LIST_INFO = 3,
    STARTED_GAME_ACK = 4,
    WORLD = 5
};

enum returnCode {
    OK,
    ERROR_FULL,
    ERROR_EXISTS
};

class ClientUpdate {
protected:
    uint8_t id;
    uint8_t returnCode;
    std::vector<uint8_t> returnData;
public:
    ClientUpdate() = default;
    ClientUpdate(uint8_t& id, uint8_t& returnCode) : id(id), returnCode(returnCode) {};

    virtual ~ClientUpdate() = default;

    virtual uint8_t getId() const { return id;};
    virtual std::vector<uint8_t> getData() const { return returnData;};
    virtual uint8_t getReturnCode() const { return returnCode;};
    virtual uint8_t getType() const = 0;
};


#endif //ROCKETLEAGUE_CLIENTUPDATE_H
