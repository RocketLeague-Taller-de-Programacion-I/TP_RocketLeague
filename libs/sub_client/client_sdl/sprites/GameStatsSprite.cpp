#include "GameStatsSprite.h"

GameStatsSprite::GameStatsSprite(SDL2pp::Texture *texture, const uint8_t id, int &windowWidth, int &windowHeight,
                                 std::map<uint8_t, uint8_t> &stats, SDL2pp::Texture *digits) :
                                GameSprite(texture, id, windowWidth, windowHeight),
                                texture(*texture),
                                stats(stats),
                                digitsTexture(*digits){}

void GameStatsSprite::render(SDL2pp::Renderer &renderer) {
    // Render Score Board image
    SDL2pp::Rect dst(windowWidth/2 - SCOREBOARD_WIDTH/2, windowHeight - SCOREBOARD_HEIGHT, SCOREBOARD_WIDTH, SCOREBOARD_HEIGHT);
    renderer.Copy(texture, SDL2pp::NullOpt, dst);
    int margin = 0;
    for(auto &playerStat : stats){
        SDL2pp::Rect idSrc(DIGIT_WIDTH * playerStat.first, 0 , DIGIT_WIDTH, FONT_HEIGHT);
        SDL2pp::Rect idDst(windowWidth/2 - SCOREBOARD_WIDTH/4, SCOREBOARD_HEIGHT/3 + FONT_HEIGHT * margin, DIGIT_WIDTH, FONT_HEIGHT);
        renderer.Copy(digitsTexture, idSrc, idDst);

        SDL2pp::Rect score2Src(DIGIT_WIDTH * playerStat.second, 0 , DIGIT_WIDTH, FONT_HEIGHT);
        SDL2pp::Rect score2Dst(windowWidth/2 +SCOREBOARD_WIDTH/4, SCOREBOARD_HEIGHT/3 + FONT_HEIGHT * margin, DIGIT_WIDTH, FONT_HEIGHT);
        renderer.Copy(digitsTexture, score2Src, score2Dst);

        margin++;
    }
}
