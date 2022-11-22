//
// Created by roby on 21/11/22.
//

#include "Worldview.h"

#include <utility>

Worldview::Worldview(std::map<std::string, SDL2pp::Texture *> textures, std::map<uint8_t, GameSprite> sprites) :
 textures(std::move(textures)),
 mapSprites(std::move(sprites)){}

void Worldview::update(float dt) {
    for (auto &sprite : mapSprites) {
        sprite.second.update(dt);
    }
}

void Worldview::render(Renderer &renderer) {
    for (auto &sprite : mapSprites) {
        sprite.second.render(renderer);
    }
}
// TODO: check if we need to destroy textures
Worldview::~Worldview() = default;