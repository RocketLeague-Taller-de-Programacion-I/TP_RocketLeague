//
// Created by roby on 04/12/22.
//

#include "GameTimeSprite.h"

GameTimeSprite::GameTimeSprite(SDL2pp::Texture *texture, const uint8_t id, int &windowWidth, int &windowHeight,
                               GameTime &time) :
                                 GameSprite(texture, id, windowWidth, windowHeight),
                                 texture(*texture){
    updateSprite(time);
}

void GameTimeSprite::render(SDL2pp::Renderer &renderer) {
    SDL2pp::Rect dozenMinutesSrc(0, 0 , DIGIT_WIDTH, FONT_HEIGHT);
    SDL2pp::Rect dozenMinutesDst(MARGIN, 0, DIGIT_WIDTH, FONT_HEIGHT);
    renderer.Copy(texture, dozenMinutesSrc, dozenMinutesDst);

    SDL2pp::Rect unityMinutesSrc(DIGIT_WIDTH * minutes, 0 , DIGIT_WIDTH, FONT_HEIGHT);
    SDL2pp::Rect unityMinutesDst(MARGIN + DIGIT_WIDTH, 0, DIGIT_WIDTH, FONT_HEIGHT);
    renderer.Copy(texture, unityMinutesSrc, unityMinutesDst);

    SDL2pp::Rect dozenSecondsSrc(DIGIT_WIDTH * dozens, 0 , DIGIT_WIDTH, FONT_HEIGHT);
    SDL2pp::Rect dozenSecondsDst(MARGIN + COLON_WIDTH + DIGIT_WIDTH * 2, 0, DIGIT_WIDTH, FONT_HEIGHT);
    renderer.Copy(texture, dozenSecondsSrc, dozenSecondsDst);

    SDL2pp::Rect unitySecondsSrc(DIGIT_WIDTH * seconds, 0 , DIGIT_WIDTH, FONT_HEIGHT);
    SDL2pp::Rect unitySecondsDst(MARGIN + COLON_WIDTH + DIGIT_WIDTH * 3, 0, DIGIT_WIDTH, FONT_HEIGHT);
    renderer.Copy(texture, unitySecondsSrc, unitySecondsDst);

    SDL2pp::Rect dashSrc(COLON_X, 0,COLON_WIDTH, FONT_HEIGHT);
    SDL2pp::Rect dashDst(MARGIN + DIGIT_WIDTH*2, 0, COLON_WIDTH, FONT_HEIGHT);
    renderer.Copy(texture,dashSrc,dashDst);
}

void GameTimeSprite::updateSprite(GameTime &time) {
    // time is in seconds
    int timeInSeconds = time.getTime();
    minutes = timeInSeconds / 60;
    dozens = (timeInSeconds % 60) / 10;
    seconds = timeInSeconds % 60 % 10;
}
