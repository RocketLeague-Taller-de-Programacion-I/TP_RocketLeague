//
// Created by lucaswaisten on 12/11/22.
//

#include "ClientReceiver.h"
ClientReceiver::ClientReceiver(Socket &aSkt,
                               BlockingQueue<Action> &queue) :
                               closed(false),
                               socket(aSkt),
                               queueAction(queue) {}
/*
* Bytes que recivo del socket
* [0] -> type action
* [1] -> cantidad de jugadores
* [2]-[n] -> nombre de la partida, hasta el nop incluido
*/
void ClientReceiver::run() {

}

bool ClientReceiver::joinThread() {
    return false;
}


