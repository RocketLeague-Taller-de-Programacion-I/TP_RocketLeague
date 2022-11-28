//
// Created by roby on 27/11/22.
//

#include "WaitingForGameToStartThread.h"

void WaitingForGameToStartThread::run() {
    ClientUpdate* update; //startedGameACK
    bool popping = true;
    std::cout << "Waiting to start" << std::endl;
    while (popping) {
        //  wait for updates
        if(updatesQueue.tryPop(update) and update) {
            std::cout << "Popped " << (int )update->getType() <<  std::endl;
            std::cout << "Popped " << (int) update->getData().size() <<  std::endl;

            if(!update->getReturnCode()) {
                popping = false;
            }
        }
    }
    std::cout << "Starting Game" << std::endl;
    stop();
}

void WaitingForGameToStartThread::stop() {
    mainWindow->close();
    //pusherar update a cola de gameloop
    join();
}
