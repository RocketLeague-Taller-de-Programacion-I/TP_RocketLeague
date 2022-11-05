//
// Created by franco on 24/10/22.
//

#ifndef ROCKETLEAGUE_SERVER_H
#define ROCKETLEAGUE_SERVER_H


class Client {
public:
    Client();
    ~Client();
    void view_screen();
    void hola();
    void start();

    int qt_init(int argc, char **argv);
};


#endif //ROCKETLEAGUE_SERVER_H
