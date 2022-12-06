#include "GameStatsSprite.h"

GameStatsSprite::GameStatsSprite(SDL2pp::Texture *texture, const uint8_t id, int &windowWidth, int &windowHeight,
                                 std::map<uint8_t, uint8_t> &stats, SDL2pp::Texture *digits) :
                                GameSprite(texture, id, windowWidth, windowHeight),
                                texture(*texture),
                                stats(stats),
                                digitsTexture(digits){}

void GameStatsSprite::render(SDL2pp::Renderer &renderer) {
    // Render Score Board image
    SDL2pp::Rect dst(windowWidth/2 - SCOREBOARD_WIDTH/2, windowHeight - SCOREBOARD_HEIGHT, SCOREBOARD_WIDTH, SCOREBOARD_HEIGHT);
    renderer.Copy(texture, SDL2pp::NullOpt, dst);
//
//    SDL2pp::Rect localTextSrc(LOCALX, 0 , LOCAL_WIDTH, FONT_HEIGHT);
//    SDL2pp::Rect localTextDst(windowWidth / 2 - LOCAL_DST_X, 0, LOCAL_WIDTH, FONT_HEIGHT);
//    renderer.Copy(texture, localTextSrc, localTextDst);
//
//    SDL2pp::Rect visitorTextSrc(VISITORX, 0 , VISITOR_WIDTH, FONT_HEIGHT);
//    SDL2pp::Rect visitorTextDst(windowWidth / 2 + VISITOR_DST_X, 0, VISITOR_WIDTH, FONT_HEIGHT);
//    renderer.Copy(texture, visitorTextSrc, visitorTextDst);
//
//    SDL2pp::Rect localGoalsSrc(DIGIT_WIDTH * localGoals, 0 , DIGIT_WIDTH, FONT_HEIGHT);
//    SDL2pp::Rect localGoalsDst(windowWidth / 2 - 3 * DIGIT_WIDTH / 2, 0, DIGIT_WIDTH, FONT_HEIGHT);
//    renderer.Copy(texture, localGoalsSrc, localGoalsDst);
//
//    SDL2pp::Rect visitorGoalsSrc(DIGIT_WIDTH * visitorGoals, 0 , DIGIT_WIDTH, FONT_HEIGHT);
//    SDL2pp::Rect visitorGoalsDst(windowWidth / 2 + DIGIT_WIDTH / 2 , 0, DIGIT_WIDTH, FONT_HEIGHT);
//    renderer.Copy(texture, visitorGoalsSrc, visitorGoalsDst);
//
//    SDL2pp::Rect dashSrc(DASHX, 0, DASH_WIDTH, FONT_HEIGHT);
//    SDL2pp::Rect dashDst(windowWidth/2 - DASH_WIDTH/2, 0, DASH_WIDTH, FONT_HEIGHT);
//    renderer.Copy(texture,dashSrc,dashDst);
}
