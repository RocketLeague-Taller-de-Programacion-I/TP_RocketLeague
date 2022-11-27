//
// Created by roby on 21/11/22.
//

#ifndef ROCKETLEAGUE_GAMESPRITE_H
#define ROCKETLEAGUE_GAMESPRITE_H

#include "libSDL2pp/SDL2pp/SDL2pp.hh"
#include "Animation.h"
struct Color {
    uint8_t r, g, b;
};
class GameSprite {
public:
    GameSprite(SDL2pp::Texture *texture, const uint8_t id, int x, int y, uint8_t angle);
    ~GameSprite();
    void update(float dt);
    void render(SDL2pp::Renderer &renderer);
private:
    Animation an;
    uint8_t id;
    int x;
    int y;
    uint8_t angle;
    bool facingLeft;
    int width;
    int height;
};


#endif //ROCKETLEAGUE_GAMESPRITE_H
