#ifndef ROCKETLEAGUE_GAMESPRITE_H
#define ROCKETLEAGUE_GAMESPRITE_H

#include "libSDL2pp/SDL2pp/SDL2pp.hh"
#include "Ball.h"
#include "Score.h"
#include "GameTime.h"
#include "Car.h"

class GameSprite {
protected:
    uint8_t id;
    int windowWidth;
    int windowHeight;
public:
    GameSprite(SDL2pp::Texture *texture, const uint8_t id, int &windowWidth, int &windowHeight) :
                                id(id),
                                windowWidth(windowWidth),
                                windowHeight(windowHeight) {};
    virtual ~GameSprite() = default;

    virtual void update(float dt){};
    virtual void updateSprite(Ball &ball) = 0;
    virtual void updateSprite(Score &score) = 0;
    virtual void updateSprite(GameTime &time) = 0;
    virtual void updateSprite(Car &car) = 0;
    virtual void render(SDL2pp::Renderer &renderer) = 0;
};


#endif //ROCKETLEAGUE_GAMESPRITE_H
