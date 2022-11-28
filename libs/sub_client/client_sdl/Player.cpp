#include "Player.h"

Player::Player(SDL2pp::Texture &texture): an(texture), facingLeft(false), movingX(false), movingY(false), x(0), y(0) {}

Player::~Player() {}

/**
 * Notar que el manejo de eventos y la actualización de modelo ocurren en momentos distintos.
 * Esto les va a resultar muy util. 
 */
void Player::update(float dt) {
    if (movingX) {
        an.update(dt);
        if (facingLeft)
            x -= 1;
        else{
            x += 1;
        }
    }
    if (movingY) {
        an.update(dt);
        if (facingUp)
            y -= 1;
        else {
            y += 1;
        }
    }
}

void Player::render(SDL2pp::Renderer &renderer) {
    SDL_RendererFlip flip = facingLeft ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
    an.render(renderer, SDL2pp::Rect(x, y, 450, 200), flip);
}

