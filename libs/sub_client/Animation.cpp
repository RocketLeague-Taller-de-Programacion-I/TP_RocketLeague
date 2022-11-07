//
// Created by franco on 02/11/22.
//

#include "Animation.h"
#include <SDL2pp/SDL2pp.hh>

#include <algorithm>
#include <cassert>
#include <iostream>
#include <string>

#include "Animation.h"

Animation::Animation(SDL2pp::Texture &texture) : texture(texture), currentFrame(0),
                                                 numFrames(1),
                                                 size(this->texture.GetHeight()), elapsed(0.0f) {
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
void Animation::render(SDL2pp::Renderer &renderer, const SDL2pp::Rect dst, SDL_RendererFlip &flipType) {
    renderer.Copy(
            texture,
            SDL2pp::Rect(0, 0, this->size*2.4, this->size),
            dst,
            0.0,                // don't rotate
            SDL2pp::NullOpt,    // rotation center - not needed
            flipType
    );
}