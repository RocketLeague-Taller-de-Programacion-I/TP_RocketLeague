//
// Created by roby on 21/11/22.
//

#include "GameSprite.h"

/**
 * Notar que el manejo de eventos y la actualización de modelo ocurren en momentos distintos.
 * Esto les va a resultar muy util.
 */
GameSprite::GameSprite(SDL2pp::Texture *texture, const uint8_t id, int x, int y, uint8_t angle)
        : an(*texture), id(id), x(x), y(y), angle(angle), facingLeft(false), width(texture->GetWidth()), height(texture->GetHeight()){}

void GameSprite::update(float dt) {
    an.update(dt);
}

void GameSprite::render(SDL2pp::Renderer &renderer) {
    SDL_RendererFlip flip = facingLeft ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
    an.render(renderer, SDL2pp::Rect(x, y, width, height), flip);
}

GameSprite::~GameSprite() {}
