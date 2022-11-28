//
// Created by roby on 24/11/22.
//

#include "ServerCreateACK.h"
#include "sub_server/ServerProtocolo.h"

void ServerCreateACK::beSerialized(Protocolo *protocolo) {
    protocolo->serializeCreateACK(this);
}

uint8_t ServerCreateACK::getType() const {
    return CREATE_ACK;
}

