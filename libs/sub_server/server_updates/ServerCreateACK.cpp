//
// Created by roby on 24/11/22.
//

#include "ServerCreateACK.h"
#include "sub_server/ServerProtocolo.h"

uint8_t ServerCreateACK::getType() const {
    return CREATE_ACK;
}

void
ServerCreateACK::beSerialized(ServerProtocolo *protocolo, std::function<void(void *, unsigned int)> &sendCallable) {
    protocolo->serializeCreateACK(this, sendCallable);
}

