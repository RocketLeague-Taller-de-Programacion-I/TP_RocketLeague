#ifndef ROCKETLEAGUE_CARSPRITE_H
#define ROCKETLEAGUE_CARSPRITE_H

#include "GameSprite.h"
#include "sub_client/client_sdl/Animation.h"

#define PXM 37 //  Pixeles por metro
#define CAR_W_PX 67
#define CAR_H_PX 30

class CarSprite : public GameSprite {
private:
    int carWidth;
    int carHeight;

    Animation an;
    bool facingWhere;
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
