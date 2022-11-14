//
// Created by lucaswaisten on 12/11/22.
//

#ifndef ROCKETLEAGUE_UPDATE_H
#define ROCKETLEAGUE_UPDATE_H


#include "Information.h"

class Update : public Information {
public:
    explicit Update(uint8_t aType,
                    std::string aData);

};


#endif //ROCKETLEAGUE_UPDATE_H
