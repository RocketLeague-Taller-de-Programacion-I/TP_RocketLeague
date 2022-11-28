//
// Created by roby on 24/11/22.
//

#ifndef ROCKETLEAGUE_SERVERUPDATE_H
#define ROCKETLEAGUE_SERVERUPDATE_H

class Protocolo;
#include <cstdint>
#include <string>
#include <vector>
#include <netinet/in.h>

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
    ServerUpdate(const uint8_t &id, uint8_t &returnCode) : id(id), returnCode(returnCode) {};
    ServerUpdate(uint8_t &id, uint8_t &returnCode, std::vector<uint8_t> &returnData) : id(id), returnCode(returnCode), returnData(returnData) {};
    virtual ~ServerUpdate() = default;

    virtual uint8_t getType() const = 0;
    virtual uint8_t getId() const { return id; };
    virtual uint8_t getReturnCode() const { return returnCode; };
    virtual std::vector<uint8_t> getReturnData() const { return returnData; };
    virtual void beSerialized(Protocolo *protocolo) = 0;
};


#endif //ROCKETLEAGUE_SERVERUPDATE_H
