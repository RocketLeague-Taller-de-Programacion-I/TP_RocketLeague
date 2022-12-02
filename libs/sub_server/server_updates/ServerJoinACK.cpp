//
// Created by roby on 24/11/22.
//

#include "ServerJoinACK.h"
#include "sub_server/ServerProtocolo.h"

void ServerJoinACK::beSerialized(ServerProtocolo *protocolo, std::function<void(void *, unsigned int)> &sendCallable) {
    protocolo->serializeJoinACK(this, sendCallable);
}

uint8_t ServerJoinACK::getType() const {
    return JOIN_ACK;
}
