//
// Created by lucaswaisten on 12/11/22.
//

#include <algorithm>
#include "MonitorSocket.h"

MonitorSocket::MonitorSocket(Socket socket) : skt(std::move(socket)) {}
