//
// Created by franco on 02/11/22.
//

#ifndef ROCKETLEAGUE_PLAYER_H
#define ROCKETLEAGUE_PLAYER_H

#include <SDL2pp/SDL2pp.hh>
#include "Animation.h"
class Player {
public:
    Player(SDL2pp::Texture &texture);
    ~Player();
    void update(float dt);
    void render(SDL2pp::Renderer &renderer);
    void moveRight();
    void moveLeft();
    void stopMoving();

    void moveDown();

    void moveUp();

private:
    Animation an;
    bool facingLeft;
    bool moving;
    int x;
    int y;
};

#endif //ROCKETLEAGUE_PLAYER_H
