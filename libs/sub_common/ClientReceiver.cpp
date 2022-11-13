//
// Created by lucaswaisten on 12/11/22.
//

#include "ClientReceiver.h"

ClientReceiver::ClientReceiver(Socket &skt) : skt_client(skt) {}

void ClientReceiver::run() {

}

bool ClientReceiver::joinThread() {
    return false;
}
