#include "ScoreSprite.h"

ScoreSprite::ScoreSprite(SDL2pp::Texture *texture, const uint8_t id, int &windowWidth, int &windowHeight,
                         Score &score) :
                         GameSprite(texture, id, windowWidth, windowHeight),
                         texture(*texture),
                         localGoals(score.getLocal()),
                         visitorGoals(score.getVisitor()) {}

void ScoreSprite::render(SDL2pp::Renderer &renderer) {
    SDL2pp::Rect localTextSrc(LOCALX, 0 , LOCAL_WIDTH, FONT_HEIGHT);
    SDL2pp::Rect localTextDst(windowWidth / 2 - LOCAL_DST_X, 0, LOCAL_WIDTH, FONT_HEIGHT);
    renderer.Copy(texture, localTextSrc, localTextDst);

    SDL2pp::Rect visitorTextSrc(VISITORX, 0 , VISITOR_WIDTH, FONT_HEIGHT);
    SDL2pp::Rect visitorTextDst(windowWidth / 2 + VISITOR_DST_X, 0, VISITOR_WIDTH, FONT_HEIGHT);
    renderer.Copy(texture, visitorTextSrc, visitorTextDst);

    SDL2pp::Rect localGoalsSrc(DIGIT_WIDTH * localGoals, 0 , DIGIT_WIDTH, FONT_HEIGHT);
    SDL2pp::Rect localGoalsDst(windowWidth / 2 - 3 * DIGIT_WIDTH / 2, 0, DIGIT_WIDTH, FONT_HEIGHT);
    renderer.Copy(texture, localGoalsSrc, localGoalsDst);

    SDL2pp::Rect visitorGoalsSrc(DIGIT_WIDTH * visitorGoals, 0 , DIGIT_WIDTH, FONT_HEIGHT);
    SDL2pp::Rect visitorGoalsDst(windowWidth / 2 + DIGIT_WIDTH / 2 , 0, DIGIT_WIDTH, FONT_HEIGHT);
    renderer.Copy(texture, visitorGoalsSrc, visitorGoalsDst);

    SDL2pp::Rect dashSrc(DASHX, 0, DASH_WIDTH, FONT_HEIGHT);
    SDL2pp::Rect dashDst(windowWidth/2 - DASH_WIDTH/2, 0, DASH_WIDTH, FONT_HEIGHT);
    renderer.Copy(texture,dashSrc,dashDst);
}

void ScoreSprite::updateSprite(Score &score) {
    localGoals = score.getLocal();
    visitorGoals = score.getVisitor();
    //if localGoals or visitorGoals are bigger than 9, reset both to 0
    if (localGoals > 9 || visitorGoals > 9){
        localGoals = 0;
        visitorGoals = 0;
    }
}
