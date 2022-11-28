//
// Created by roby on 25/11/22.
//

#include "ServerUpdateWorld.h"

uint16_t ServerUpdateWorld::getType() const {
    return WORLD;
}

std::vector<uint16_t> ServerUpdateWorld::beSerialized() { //TODO: check how to serialize
    std::vector<uint16_t> worldData;
    worldData.push_back(getType());
    worldData.insert(worldData.end(), returnData.begin(), returnData.end());
    return worldData;
}
