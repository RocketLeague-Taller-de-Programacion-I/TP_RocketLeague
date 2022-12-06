#ifndef ROCKETLEAGUE_CLIENTUPDATE_H
#define ROCKETLEAGUE_CLIENTUPDATE_H

#include <map>
#include <vector>
#include <string>
#include "sub_client/client_sdl/Ball.h"
#include "sub_client/client_sdl/Score.h"
#include "sub_client/client_sdl/Car.h"
#include "sub_client/client_sdl/GameTime.h"

enum updateType {
    CREATE_ACK = 1,
    JOIN_ACK = 2,
    LIST_INFO = 3,
    STARTED_GAME_ACK = 4,
    WORLD = 5,
    GAME_OVER = 6,
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

    virtual Ball getBall() ;
    virtual Score getScore() ;
    virtual GameTime getTime() ;
    virtual std::vector<Car> getCars() ;
    virtual std::map<std::string, std::string> getList();
    virtual std::map<uint8_t,uint8_t> getStats();
};


#endif //ROCKETLEAGUE_CLIENTUPDATE_H
