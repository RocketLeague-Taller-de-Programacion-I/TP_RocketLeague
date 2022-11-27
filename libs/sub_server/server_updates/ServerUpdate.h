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
    STARTED_GAME_ACK = 4,
    WORLD = 5,
};
enum returnCode {
    OK,
    ERROR_FULL,
    ERROR_EXISTS
};
class ServerUpdate {
protected:
    uint8_t id;
    uint8_t returnCode;
    std::vector<uint8_t> returnData;
public:
    ServerUpdate(const uint8_t &id, uint8_t& returnCode) : id(id), returnCode(returnCode) {};
    ServerUpdate(uint8_t &id, uint8_t &returnCode, std::vector<uint8_t> &returnData) : id(id), returnCode(returnCode), returnData(returnData) {};
    virtual ~ServerUpdate() = default;

    virtual std::uint8_t getType() const = 0; //TODO> to change name or remove
    virtual uint8_t getReturnCode() const { return returnCode; };
    virtual std::vector<uint8_t> beSerialized() = 0;
};


#endif //ROCKETLEAGUE_SERVERUPDATE_H
