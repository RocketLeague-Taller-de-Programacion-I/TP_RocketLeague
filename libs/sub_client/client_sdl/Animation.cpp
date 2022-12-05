//
// Created by franco on 02/11/22.
//

#include "Animation.h"
#include "libSDL2pp/SDL2pp/SDL2pp.hh"

#include <algorithm>
#include <cassert>
#include <iostream>
#include <string>

#include "Animation.h"

Animation::Animation(SDL2pp::Texture &texture) : texture(texture), currentFrame(0),
                                                 numFrames(1),
                                                 size(texture.GetHeight()), elapsed(0.0f) {
    assert(this->numFrames > 0);
    assert(this->size > 0);
}

Animation::~Animation() {}

void Animation::update(float dt) {
    this->elapsed += dt;
    /* checks if the frame should be updated based on the time elapsed since the last update */
    while (this->elapsed > FRAME_RATE) {
        // this->advanceFrame();
        this->elapsed -= FRAME_RATE;
    }
}

/**
 * @brief Renders the animation in the given coordinates.
 *
 * @param renderer Renderer.
 * @param x X coordinate.
 * @param y Y corrdinate.
 */
 //  TODO: Revisar

void Animation::render(SDL2pp::Renderer &renderer, const SDL2pp::Rect dst, SDL_RendererFlip &flipType, int &angle) {
    renderer.Copy(
            texture,
            SDL2pp::NullOpt,
            dst,
            angle,                // don't rotate
            SDL2pp::NullOpt,    // rotation center - not needed
            flipType
    );
}


//QT
//SDL (create-> posicion, join, join con la partida epezo)
// creanos el car propio --> hardocdeadola posicion
// cear el score --> 0:0
// crear el ball -> piso
//gamelopop