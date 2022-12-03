//
// Created by roby on 24/11/22.
//

#include "ServerJoinACK.h"
#include "sub_server/ServerProtocolo.h"

void ServerJoinACK::beSerialized(ServerProtocolo *protocolo) {
    protocolo->serializeJoinACK(this);
}

uint8_t ServerJoinACK::getType() const {
    return JOIN_ACK;
}
