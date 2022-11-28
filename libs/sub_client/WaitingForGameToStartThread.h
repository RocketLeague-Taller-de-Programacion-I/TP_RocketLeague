//
// Created by roby on 27/11/22.
//

#ifndef ROCKETLEAGUE_WAITINGFORGAMETOSTARTTHREAD_H
#define ROCKETLEAGUE_WAITINGFORGAMETOSTARTTHREAD_H


#include "sub_common/thread.h"
#include "sub_client/client_qt/mainwindow.h"

class WaitingForGameToStartThread : public Thread {
private:
    MainWindow* mainWindow;
    ProtectedQueue<std::shared_ptr<ClientUpdate>> &updatesQueue;
protected:
    void run() override;
public:
    void stop() override;
    WaitingForGameToStartThread(MainWindow *window, ProtectedQueue<std::shared_ptr<ClientUpdate>> &queue) : mainWindow(window), updatesQueue(queue) {};
    explicit WaitingForGameToStartThread();

    ~WaitingForGameToStartThread() override { join(); };
};


#endif //ROCKETLEAGUE_WAITINGFORGAMETOSTARTTHREAD_H
