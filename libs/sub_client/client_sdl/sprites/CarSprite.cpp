#include "CarSprite.h"

CarSprite::CarSprite(SDL2pp::Texture *texture, const uint8_t id, int &windowWidth, int &windowHeight, Car &car) :
        GameSprite(texture,id,windowWidth,windowHeight),
        an(*texture),
        carWidth(texture->GetWidth()),
        carHeight(texture->GetHeight()){
    updateSprite(car);
}

void CarSprite::update(float dt) {
    an.update(dt);
}

void CarSprite::updateSprite(Car &car) {
    positionX = (car.getX() * PXM) - CAR_W_PX/2;
    positionY = windowHeight - (car.getY() * PXM) - CAR_H_PX/2;
    angle = car.getAngle();
    facingWhere = car.getFacing(); //true ->left , false->right
}

void CarSprite::render(SDL2pp::Renderer &renderer) {
    SDL_RendererFlip flip = (facingWhere == RIGHT) ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
    an.render(renderer, SDL2pp::Rect(positionX, positionY, carWidth, carHeight), flip, angle);
}
