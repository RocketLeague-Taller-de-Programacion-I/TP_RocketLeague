//
// Created by roby on 21/11/22.
//

#include "Worldview.h"


// id: 2
//id: 0 -> ball
//id: 1 -> score
Worldview::Worldview(std::map<std::string, SDL2pp::Texture *> textures, std::map<uint8_t, GameSprite> sprites) :
 textures(std::move(textures)),
 mapSprites(std::move(sprites)){}

void Worldview::update(float dt) {
    for (auto &sprite : mapSprites) {
        sprite.second.update(dt);
    }
}

void Worldview::render(Renderer &renderer) {
    //  render field
    renderer.Copy(*textures[FIELD_TEXT], SDL2pp::NullOpt, SDL2pp::NullOpt);
    for (auto &sprite : mapSprites) {
        sprite.second.render(renderer);
    }
}

void Worldview::updateSprites(Ball &ball, Score &score, std::vector<Car> &players) {
    // check if sprite BALL exists in mapSprites

    if(mapSprites.find(BALL) == mapSprites.end()){
        mapSprites.emplace(BALL, GameSprite(textures[BALL_TEXT],BALL, ball.getX(), ball.getY(), 0));
    } else {
        mapSprites.at(BALL).setX(ball.getX());
        mapSprites.at(BALL).setY(ball.getY());
    }

    if (mapSprites.find(SCORE) == mapSprites.end()) {
        mapSprites.emplace(SCORE, GameSprite(textures[SCORE_TEXT], SCORE, score.getLocal(), score.getVisitor(), 0));
    } else {
        mapSprites.at(SCORE).setX(score.getLocal());
        mapSprites.at(SCORE).setY(score.getVisitor());
    }

    for (auto & player : players) {
        uint8_t id = player.getId();
        if (mapSprites.find(id) == mapSprites.end()) {
            mapSprites.emplace(id, GameSprite(textures[CAR_TEXT], id, player.getX(), player.getY(), player.getAngle()));
        } else {
            mapSprites.at(id).setX(player.getX());
            mapSprites.at(id).setY(player.getY());
            mapSprites.at(id).setAngle(player.getAngle());
        }
    }
}


// TODO: check if we need to destroy textures
Worldview::~Worldview() = default;