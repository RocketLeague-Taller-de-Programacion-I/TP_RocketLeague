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
//    ServerUpdate(uint8_t &id, std::vector<uint8_t> &data) : id(id), data(data) {};
    virtual ~ServerUpdate() = default;

    virtual std::uint8_t getType() const = 0;
    virtual std::string getReturnData() const { return std::string(returnData.begin(), returnData.end()); }; //TODO> to change name or remove
    virtual std::vector<uint8_t> getData() const { return returnData; };
    virtual uint8_t getReturnCode() const { return returnCode; };
    virtual std::vector<uint8_t> beSerialized() = 0;
};


#endif //ROCKETLEAGUE_SERVERUPDATE_H
