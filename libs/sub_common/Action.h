//
// Created by lucaswaisten on 12/11/22.
//

#ifndef ROCKETLEAGUE_ACTION_H
#define ROCKETLEAGUE_ACTION_H

#include <string>
#include <vector>

enum actionType {
    CREATE_ROOM = 1,
    JOIN_ROOM,
    LIST_ROOMS,
    MOVE,
    UPDATE
};


class Action {
protected:
    uint8_t idInvoker;
public:
    Action();
    explicit Action(uint8_t &id);

    virtual ~Action();

    virtual uint8_t getId();
    virtual void execute();
    virtual std::vector<uint8_t> beSerialized();
};


#endif //ROCKETLEAGUE_ACTION_H
