#ifndef ROCKETLEAGUE_BALLSPRITE_H
#define ROCKETLEAGUE_BALLSPRITE_H

#include "GameSprite.h"
#define PXM 37 //  Pixeles por metro

#define BALL_W_PX 55
#define BALL_H_PX 48
class BallSprite : public GameSprite {
private:
    SDL2pp::Texture &texture;

    int ballWidth;
    int ballHeight;

    int positionX;
    int positionY;
public:
    BallSprite(SDL2pp::Texture *texture, const uint8_t id, int &windowWidth, int &windowHeight, Ball& ball);
    ~BallSprite() = default; //TODO: free surface?

    void updateSprite(Ball &ball) override;
    void updateSprite(Score &score) override {};
    void updateSprite(GameTime &time) override {};
    void updateSprite(Car &car) override {};
    void render(SDL2pp::Renderer &renderer) override;
};


#endif //ROCKETLEAGUE_BALLSPRITE_H
