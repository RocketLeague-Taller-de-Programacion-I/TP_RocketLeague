//
// Created by roby on 24/11/22.
//

#ifndef ROCKETLEAGUE_SERVERUPDATE_H
#define ROCKETLEAGUE_SERVERUPDATE_H

class ServerProtocolo;
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
};
class ServerUpdate {
protected:
    uint8_t id;
    uint8_t returnCode;
public:
    ServerUpdate() {
        id = 0;
        returnCode = 0;
    };
    ServerUpdate(const uint8_t &id, uint8_t &returnCode) : id(id), returnCode(returnCode) {};
    virtual ~ServerUpdate() = default;

    virtual uint8_t getType() const = 0;
    virtual uint8_t getId() const { return id; };
    virtual uint8_t getReturnCode() const { return returnCode; };
    virtual void beSerialized(ServerProtocolo *protocolo, std::function<void(void *, unsigned int)> &sendCallable) = 0;
};


#endif //ROCKETLEAGUE_SERVERUPDATE_H
