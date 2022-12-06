//
// Created by roby on 27/11/22.
//

#include "ClientActionMove.h"
#include "sub_client/ClientProtocol.h"

ClientActionMove::ClientActionMove(uint8_t &idPlayer, uint8_t &direction, bool state) :
                                idPlayer(idPlayer),
                                direction(direction),
                                state(state){
    type = MOVE;
}

void ClientActionMove::beSerialized(ClientProtocol *p) {
    p->serializeMove(this);
}