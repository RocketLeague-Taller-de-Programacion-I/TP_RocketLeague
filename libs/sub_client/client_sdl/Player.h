//
// Created by franco on 02/11/22.
//

#ifndef ROCKETLEAGUE_PLAYER_H
#define ROCKETLEAGUE_PLAYER_H

#include "libSDL2pp/SDL2pp/SDL2pp.hh"
#include "Animation.h"
class Player {
public:
    explicit Player(SDL2pp::Texture &texture);
    ~Player();
    void update(float dt);
    void render(SDL2pp::Renderer &renderer);

private:
    Animation an;
    bool facingLeft;
    bool facingUp;
    bool movingX;
    bool movingY;
    uint16_t x;
    uint16_t y;
    uint16_t angle;
};

#endif //ROCKETLEAGUE_PLAYER_H
