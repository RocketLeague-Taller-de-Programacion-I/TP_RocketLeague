#include "Worldview.h"

Worldview::Worldview(std::map<std::string, SDL2pp::Texture *> textures, int &windowWidth, int &windowHeight) :
        textures(std::move(textures)),
        windowWidth(windowWidth),
        windowHeight(windowHeight){}

//void Worldview::update(float dt) {
//    for (auto &sprite : mapSprites) {
//        sprite.second.update(dt);
//    }
//}

void Worldview::render(Renderer &renderer) {
    //  render field
    renderer.Copy(*textures[FIELD_TEXT], SDL2pp::NullOpt, SDL2pp::NullOpt);

    for (auto &sprite : mapSprites) {
        sprite.second->render(renderer);
    }
}

void Worldview::updateSprites(Ball &ball, Score &score, std::vector<Car> &players) {
    // check if sprite BALL exists in mapSprites
    if(mapSprites.find(BALL) == mapSprites.end()){
        auto ballSprite = new BallSprite(textures[BALL_TEXT], BALL, windowWidth, windowHeight, ball);
        mapSprites.insert(std::pair<uint8_t, GameSprite*>(BALL, ballSprite));
    } else {
        mapSprites.at(BALL)->updateSprite(ball);
    }

    if (mapSprites.find(SCORE) == mapSprites.end()) {
        auto scoreSprite = new ScoreSprite(textures[SCORE_TEXT], SCORE, windowWidth, windowHeight, score);
        mapSprites.insert(std::pair<uint8_t, GameSprite*>(SCORE, scoreSprite));
    } else {
        mapSprites.at(SCORE)->updateSprite(score);
    }

    for (auto & player : players) {
        uint8_t id = player.getId();
        if (mapSprites.find(id) == mapSprites.end()) {
            // if id is even -> red car
            std::string carColor = (id % 2 == 0) ? RED_CAR_TEXT : BLUE_CAR_TEXT;
            auto carSprite = new CarSprite(textures[carColor], id, windowWidth, windowHeight, player);
            mapSprites.insert(std::pair<uint8_t, GameSprite*>(id, carSprite));
        } else {
            mapSprites.at(id)->updateSprite(player);
        }
    }
}


// TODO: check if we need to destroy textures
Worldview::~Worldview() = default;