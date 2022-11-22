//
// Created by lucaswaisten on 22/11/22.
//

#ifndef ROCKETLEAGUE_ACTIONMAKER_H
#define ROCKETLEAGUE_ACTIONMAKER_H


#include <vector>
#include "gameManager.h"

class ActionMaker {

public:
    Action * makeAction(std::vector<uint8_t> &data, GameManager &manager,
                        std::function<void(BlockingQueue<Action *> *, BlockingQueue<Action *> *)> function);

    Action *makeCreateAction(std::vector<uint8_t> &data, GameManager &manager,
                             std::function<void(BlockingQueue<Action *> *, BlockingQueue<Action *> *)> function);

    Action *makeJoinAction(std::vector<uint8_t> &data, GameManager &manager,
                           std::function<void(BlockingQueue<Action *> *, BlockingQueue<Action *> *)> function);

    Action *makeListAction(std::vector<uint8_t> &vector, GameManager &manager,
                           std::function<void(BlockingQueue<Action *> *, BlockingQueue<Action *> *)> function);

    Action *makeUpdateAction(std::vector<uint8_t> &vector);
};


#endif //ROCKETLEAGUE_ACTIONMAKER_H
