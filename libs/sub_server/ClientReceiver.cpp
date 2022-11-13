//
// Created by lucaswaisten on 12/11/22.
//

#include "ClientReceiver.h"
ClientReceiver::ClientReceiver(Socket &aSkt,
                               BlockingQueue<Action> &queue) :
                               closed(false),
                               socket(aSkt),
                               queueAction(queue) {}
void ClientReceiver::run() {

}

bool ClientReceiver::joinThread() {
    return false;
}


