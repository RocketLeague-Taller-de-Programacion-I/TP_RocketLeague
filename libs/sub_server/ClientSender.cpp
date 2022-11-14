//
// Created by lucaswaisten on 12/11/22.
//

#include "ClientSender.h"

ClientSender::ClientSender(Socket &aSkt,
                           BlockingQueue<Update> &queue) :
                           closed(false),
                           socket(aSkt),
                           queueUpdates(queue){

}
void ClientSender::run() {
    while (not closed) {

    }

}

bool ClientSender::joinThread() {
    return false;
}




