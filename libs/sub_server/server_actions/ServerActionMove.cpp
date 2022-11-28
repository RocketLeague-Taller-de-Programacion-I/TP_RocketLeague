//
// Created by roby on 27/11/22.
//

#include "ServerActionMove.h"

void ServerActionMove::execute(Match &match) {
    switch (direction) {
        case RIGHT:
            match.moveRight(id, state);
            break;
        case LEFT:
            match.moveLeft(id, state);
            break;
        case JUMP:
            match.jump(id, state);
            break;
        case TURBO:
            match.turbo(id, state);
            break;
    }
}
