//
// Created by roby on 21/11/22.
//

#ifndef ROCKETLEAGUE_WORLDVIEW_H
#define ROCKETLEAGUE_WORLDVIEW_H

#include "libSDL2pp/SDL2pp/SDL2pp.hh"
#include <map>
#include "Animation.h"
#include "GameSprite.h"

using namespace SDL2pp;

enum ids {
    SCORE=6,
    BALL,
    CAR
};


class Worldview {
private:
    std::map<std::string, Texture *> textures;
    // map of Sprite
    std::map<uint8_t, GameSprite> mapSprites;

public:
    Worldview(std::map<std::string, Texture *> textures, std::map<uint8_t, GameSprite> mapSprites);
    ~Worldview();
    void render(SDL2pp::Renderer &renderer);
    void update(float dt);
};


#endif //ROCKETLEAGUE_WORLDVIEW_H
