#include "ServerActionMove.h"

ServerActionMove::ServerActionMove(const uint8_t &id, uint8_t &direction, bool &state) :
        ServerAction(id),
        direction(direction),
        state(state) {}

void ServerActionMove::execute(Match &match) {
    switch (direction) {
        case RIGHT_D:
            match.moveRight(id, state);
            break;
        case LEFT_D:
            match.moveLeft(id, state);
            break;
        case JUMP_D:
            match.jump(id, state);
            break;
        case TURBO_D:
            match.turbo(id, state);
            break;
    }
}
