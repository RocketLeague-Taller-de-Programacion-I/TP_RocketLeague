#ifndef ROCKETLEAGUE_CARSPRITE_H
#define ROCKETLEAGUE_CARSPRITE_H

#include "GameSprite.h"
#include "Animation.h"

class CarSprite : public GameSprite {
private:
    int carWidth;
    int carHeight;

    Animation an;
    bool facingLeft;
    int positionX;
    int positionY;
    uint16_t angleSign;
    int angle;

public:
    CarSprite(SDL2pp::Texture *texture, const uint8_t id, int &windowWidth, int &windowHeight, Car& car);
    ~CarSprite() = default; //TODO: free surface?

    void update(float dt) override;
    void updateSprite(Car &car) override;
    void updateSprite(Ball &ball) override {};
    void updateSprite(GameTime &time) override {};
    void updateSprite(Score &score) override {};
    void render(SDL2pp::Renderer &renderer) override;
};


#endif //ROCKETLEAGUE_CARSPRITE_H
