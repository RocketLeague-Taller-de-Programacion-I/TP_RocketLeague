#ifndef ROCKETLEAGUE_GAMESTATSSPRITE_H
#define ROCKETLEAGUE_GAMESTATSSPRITE_H


#include <map>
#include "GameSprite.h"

#define SCOREBOARD_WIDTH 800
#define SCOREBOARD_HEIGHT 605
#define FONT_HEIGHT 69
#define DIGIT_WIDTH  43

class GameStatsSprite : public GameSprite {
private:
    SDL2pp::Texture &texture;
    SDL2pp::Texture &digitsTexture;
    std::map<uint8_t,uint8_t> stats;
public:
    GameStatsSprite(SDL2pp::Texture *texture, const uint8_t id, int &windowWidth, int &windowHeight,
                    std::map<uint8_t, uint8_t> &stats, SDL2pp::Texture *digits);
    ~GameStatsSprite() override = default;

    void updateSprite(Score &score) override{};
    void updateSprite(GameTime &time) override {};
    void updateSprite(Car &car) override {};
    void updateSprite(Ball &ball) override {};
    void render(SDL2pp::Renderer &renderer) override;

};


#endif //ROCKETLEAGUE_GAMESTATSSPRITE_H
