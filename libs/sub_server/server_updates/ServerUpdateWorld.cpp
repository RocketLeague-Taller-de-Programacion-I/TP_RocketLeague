//
// Created by roby on 25/11/22.
//

#include "ServerUpdateWorld.h"
#include "sub_server/ServerProtocolo.h"
uint8_t ServerUpdateWorld::getType() const {
    return WORLD;
}

std::vector<uint8_t> ServerUpdateWorld::beSerialized() { //TODO: check how to serialize
    return Protocolo::serializeUpdateWorld(info);
}
