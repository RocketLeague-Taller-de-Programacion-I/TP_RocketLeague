//
// Created by roby on 27/11/22.
//

#ifndef ROCKETLEAGUE_CLIENTACTIONMOVE_H
#define ROCKETLEAGUE_CLIENTACTIONMOVE_H

#include "ClientAction.h"

class ClientActionMove : public ClientAction {
private:
    uint8_t idPlayer;
    uint8_t direction;
    bool state;
public:
    ClientActionMove(uint8_t &idPlayer, uint8_t direction, bool state);
    ~ClientActionMove() override = default;

    uint8_t getType() const override { return MOVE; };
    void beSerialized(ClientProtocol *protocolo) override;
    uint8_t getIdPlayer() const { return idPlayer; };
    uint8_t getDirection() const { return direction; };
    bool getState() const { return state; };
};


#endif //ROCKETLEAGUE_CLIENTACTIONMOVE_H
