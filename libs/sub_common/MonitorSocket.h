//
// Created by lucaswaisten on 12/11/22.
//

#ifndef ROCKETLEAGUE_MONITORSOCKET_H
#define ROCKETLEAGUE_MONITORSOCKET_H

#include "sub_common/socket.h"

class MonitorSocket {
private:
    Socket &&skt;
public:
    explicit MonitorSocket(Socket socket);

};


#endif //ROCKETLEAGUE_MONITORSOCKET_H
