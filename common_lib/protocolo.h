//
// Created by lucaswaisten on 31/10/22.
//

#ifndef ROCKETLEAGUE_PROTOCOLO_H
#define ROCKETLEAGUE_PROTOCOLO_H


#include "socket.h"

class Protocolo {
private:
    Socket socket;

public:
    explicit Protocolo(const std::string &servname);

    Protocolo(const std::string &hostname, const std::string &servname);

};


#endif //ROCKETLEAGUE_PROTOCOLO_H
