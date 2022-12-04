#ifndef ROCKETLEAGUE_SCORESPRITE_H
#define ROCKETLEAGUE_SCORESPRITE_H

#include "GameSprite.h"

#define FONT_HEIGHT 69

#define DIGIT_WIDTH  43

#define LOCAL_WIDTH 127
#define LOCALX 465
#define LOCAL_DST_X 200

#define VISITOR_WIDTH 150
#define VISITORX 592
#define VISITOR_DST_X 65

#define DASH_WIDTH  42
#define DASHX 430

class ScoreSprite : public GameSprite {
private:
    SDL2pp::Texture &texture;
    int localGoals;
    int visitorGoals;
public:
    ScoreSprite(SDL2pp::Texture *texture, const uint8_t id, int &windowWidth, int &windowHeight, Score& score);
    ~ScoreSprite() = default;

    void updateSprite(Score &score) override;
    void updateSprite(GameTime &time) override {};
    void updateSprite(Car &car) override {};
    void updateSprite(Ball &ball) override {};
    void render(SDL2pp::Renderer &renderer) override;
};


#endif //ROCKETLEAGUE_SCORESPRITE_H
