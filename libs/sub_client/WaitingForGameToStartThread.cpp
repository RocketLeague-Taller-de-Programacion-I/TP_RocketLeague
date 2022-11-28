//
// Created by roby on 27/11/22.
//

#include "WaitingForGameToStartThread.h"

void WaitingForGameToStartThread::run() {
    ClientUpdate* update; //startedGameACK
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
    delete update;
    stop();
}

void WaitingForGameToStartThread::stop() {
    mainWindow->close();
    join();
}
