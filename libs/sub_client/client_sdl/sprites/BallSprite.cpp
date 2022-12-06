#include "BallSprite.h"

BallSprite::BallSprite(SDL2pp::Texture *texture, const uint8_t id, int &windowWidth, int &windowHeight, Ball &ball) :
                GameSprite(texture, id, windowWidth, windowHeight),
                texture(*texture){
    updateSprite(ball);
}

void BallSprite::render(SDL2pp::Renderer &renderer) {
    renderer.Copy(texture,
                  SDL2pp::NullOpt,
                  SDL2pp::Rect(positionX, positionY, ballWidth, ballHeight),
                  ballAngle,                // don't rotate
                  SDL2pp::NullOpt);
}

void BallSprite::updateSprite(Ball &ball) {
    positionX = (ball.getX() * PXM) - BALL_W_PX/2; // TODO: check in match the size of the sensors
    positionY = windowHeight - (ball.getY() * PXM) - BALL_H_PX/2;
    ballAngle = ball.getAngle();

    ballWidth = texture.GetWidth();
    ballHeight = texture.GetHeight();
}
