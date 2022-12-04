#ifndef ROCKETLEAGUE_WORLDVIEW_H
#define ROCKETLEAGUE_WORLDVIEW_H

#include "libSDL2pp/SDL2pp/SDL2pp.hh"
#include <map>

#include "BallSprite.h"
#include "ScoreSprite.h"
#include "CarSprite.h"

#define BALL_TEXT "ballTexture"
#define CAR_TEXT "carTexture"
#define FIELD_TEXT "fieldTexture"
#define SCORE_TEXT "scoreTexture"

using namespace SDL2pp;

enum ids {
    BALL  = 0,
    SCORE = 1,
    FIELD = 2
};


class Worldview {
private:
    std::map<std::string, Texture *> textures;
    std::map<uint8_t, GameSprite*> mapSprites;
    int windowWidth;
    int windowHeight;
public:
    Worldview(std::map<std::string, SDL2pp::Texture *> textures, int &windowWidth, int &windowHeight);
    ~Worldview();
    void render(SDL2pp::Renderer &renderer);
    void update(float dt);

    void updateSprites(Ball &ball, Score &score, std::vector<Car> &players);
};


#endif //ROCKETLEAGUE_WORLDVIEW_H
