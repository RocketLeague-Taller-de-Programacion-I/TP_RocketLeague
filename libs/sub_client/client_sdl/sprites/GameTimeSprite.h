#ifndef ROCKETLEAGUE_GAMETIMESPRITE_H
#define ROCKETLEAGUE_GAMETIMESPRITE_H

#include "GameSprite.h"

#define MARGIN 2
#define FONT_HEIGHT 69
#define DIGIT_WIDTH  43
#define COLON_WIDTH 30
#define COLON_X 755

class GameTimeSprite : public GameSprite {
private:
    SDL2pp::Texture &texture;
    int minutes;
    int dozens;
    int seconds;
public:
    GameTimeSprite(SDL2pp::Texture *texture, const uint8_t id, int &windowWidth, int &windowHeight, GameTime &time);
    ~GameTimeSprite() = default;

    void updateSprite(GameTime &time) override;
    void updateSprite(Score &score) override {};
    void updateSprite(Car &car) override {};
    void updateSprite(Ball &ball) override {};
    void render(SDL2pp::Renderer &renderer) override;
};


#endif //ROCKETLEAGUE_GAMETIMESPRITE_H
