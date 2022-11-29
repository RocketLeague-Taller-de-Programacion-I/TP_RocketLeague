//
// Created by roby on 25/11/22.
//

#include "ServerUpdateWorld.h"
#include "sub_server/ServerProtocolo.h"

uint8_t ServerUpdateWorld::getType() const {
    return WORLD;
}

void ServerUpdateWorld::beSerialized(Protocolo *protocolo) { //TODO: check how to serialize
    protocolo->serializeWorldUpdate(this);
}
