#include "Player.h"

Player::Player(SDL2pp::Texture &texture): an(texture), facingLeft(false), movingX(false), movingY(false), x(300), y(300) {}

Player::~Player() {}

/**
 * Notar que el manejo de eventos y la actualización de modelo ocurren en momentos distintos.
 * Esto les va a resultar muy util. 
 */
void Player::update(float dt) {
    if (movingX) {
        an.update(dt);
        if (facingLeft)
            x -= 3;
        else{
            x += 3;
        }
    }
    if (movingY) {
        an.update(dt);
        if (facingUp)
            y -= 3;
        else {
            y += 3;
        }
    }
}

void Player::render(SDL2pp::Renderer &renderer) {
    SDL_RendererFlip flip = facingLeft ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
    an.render(renderer, SDL2pp::Rect(x, y, 450, 200), flip);
}

void Player::moveRight() {
    movingX = true;
    facingLeft = false;
    facingUp = false;
}

void Player::moveLeft() {
    movingX = true;
    facingLeft = true;
    facingUp = false;
}

void Player::stopMovingX() {
    movingX = false;
}
void Player::stopMovingY() {
    movingY= false;
}


void Player::moveDown() {
    movingY = true;
    facingUp = false;
}

void Player::moveUp() {
    movingY = true;
    facingUp = true;
}