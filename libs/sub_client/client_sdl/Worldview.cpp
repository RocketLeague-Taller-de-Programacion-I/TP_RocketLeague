#include "Worldview.h"

Worldview::Worldview(std::map<std::string, SDL2pp::Texture *> textures, int &windowWidth, int &windowHeight) :
        textures(std::move(textures)),
        windowWidth(windowWidth),
        windowHeight(windowHeight){
    onlinePlayers = 0;
}

void Worldview::render(Renderer &renderer) {
    //  render field
    renderer.Copy(*textures[FIELD_TEXT], SDL2pp::NullOpt, SDL2pp::NullOpt);

    for (auto &sprite : mapSprites) {
        sprite.second->render(renderer);
    }
}

void Worldview::updateSprites(Ball &ball, Score &score, GameTime &gameTime, std::vector<Car> &players) {
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

    if(mapSprites.find(TIME) == mapSprites.end()){
        auto timeSprite = new GameTimeSprite(textures[SCORE_TEXT], TIME, windowWidth, windowHeight, gameTime);
        mapSprites.insert(std::pair<uint8_t, GameSprite*>(TIME, timeSprite));
    } else {
        mapSprites.at(TIME)->updateSprite(gameTime);
    }

    for (auto & player : players) {
        uint8_t id = player.getId();
        if (mapSprites.find(id) == mapSprites.end()) {
            // if id is even -> red car
            std::string carColor = (id % 2 == 0) ? RED_CAR_TEXT : BLUE_CAR_TEXT;
            auto carSprite = new CarSprite(textures[carColor], id, windowWidth, windowHeight, player);
            mapSprites.insert(std::pair<uint8_t, GameSprite*>(id, carSprite));
            onlinePlayers++;
        } else {
            mapSprites.at(id)->updateSprite(player);
        }
    }
    //clean ids that are on the mapSprites but not in the players vector
    cleanDisconnected(players);
}

void Worldview::cleanDisconnected(std::vector<Car> &players) {
    std::vector<uint8_t> idsToDelete;
    for (auto & sprite : mapSprites) {
        uint8_t id = sprite.first;
        if (id != BALL && id != SCORE && id != TIME) {
            bool found = false;
            for (auto & player : players) {
                if (player.getId() == id) {
                    found = true;
                    break;
                }
            }
            if (!found) {
                delete sprite.second;
                idsToDelete.push_back(id);
                onlinePlayers--;
            }
        }
    }
    for (auto & id : idsToDelete) {
        mapSprites.erase(id);
    }
}


void Worldview::updateStats(std::map<uint8_t, uint8_t> &stats) {
    gameStats = stats;
    cleanSprites();
    auto statsSprite = new GameStatsSprite(textures[SCORE_BOARD_TEXT], SCORE, windowWidth, windowHeight, gameStats,
                                           textures[SCORE_TEXT]);
    mapSprites.insert(std::pair<uint8_t, GameSprite*>(SCORE, statsSprite));
}

void Worldview::cleanSprites() {
    for (auto & sprite : mapSprites) {
        delete sprite.second;
    }
    mapSprites.clear();
}

// TODO: check if we need to destroy textures
Worldview::~Worldview() {
    for (auto & sprite : mapSprites) {
        delete sprite.second;
    }
}
