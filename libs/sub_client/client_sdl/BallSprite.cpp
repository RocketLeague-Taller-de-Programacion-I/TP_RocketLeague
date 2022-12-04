//
// Created by roby on 04/12/22.
//

#include "BallSprite.h"

BallSprite::BallSprite(SDL2pp::Texture *texture, const uint8_t id, int &windowWidth, int &windowHeight, Ball &ball) :
                GameSprite(texture, id, windowWidth, windowHeight),
                texture(*texture){
    updateSprite(ball);
}

void BallSprite::render(SDL2pp::Renderer &renderer) {
    renderer.Copy(texture, SDL2pp::NullOpt, SDL2pp::Rect(positionX, positionY, ballWidth, ballHeight));
}

void BallSprite::updateSprite(Ball &ball) {
    positionX = ball.getX();
    positionY = ball.getY();

    ballWidth = texture.GetWidth();
    ballHeight = texture.GetHeight();
}
