//
// Created by roby on 27/11/22.
//

#include "WaitingForGameToStartThread.h"

void WaitingForGameToStartThread::run() {
    std::shared_ptr<ClientUpdate> update; //startedGameACK
    bool popping = true;
    while (popping) {
        //  wait for updates
        if(updatesQueue.tryPop(update) and update) {
            if(!update->getReturnCode()) {
                popping = false;
            }
        }
    }
    std::cout << "Starting Game" << std::endl;
    stop();
}

void WaitingForGameToStartThread::stop() {
    join();
}
