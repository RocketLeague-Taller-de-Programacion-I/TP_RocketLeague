//
// Created by lucaswaisten on 22/11/22.
//

#include "ActionMaker.h"

#include <utility>
#include "sub_common/Action.h"
#include "ActionCreateServer.h"
#include "ActionJoinServer.h"
#include "ActionListServer.h"

Action *ActionMaker::makeAction(std::vector<uint8_t> &data, GameManager &manager,
                                std::function<void(BlockingQueue<Action *> *, BlockingQueue<Action *> *)> function) {
    uint8_t type(data[0]);

    switch (type) {
        case CREATE_ROOM:
            return makeCreateAction(data, manager, function);
        case JOIN_ROOM:
            return makeJoinAction(data, manager, function);
        case LIST_ROOMS:
            return makeListAction(data, manager, function);
        case UPDATE:
            return makeUpdateAction(data);
    }
    return {};
}

Action *ActionMaker::makeCreateAction(std::vector<uint8_t> &data, GameManager &manager,
                                      std::function<void(BlockingQueue<Action *> *,
                                                         BlockingQueue<Action *> *)> function) {
    uint8_t id(data[1]);
    int capacity(data[2]);
    std::string name(data.begin()+3,data.end());
//    std::shared_ptr<Action> pAction = std::make_shared<ActionCreateServer>(id, capacity, name);
//    std::unique_ptr<Action> pAction(new ActionCreateServer(id, capacity, std::move(name)));
    // create pointer to derived class and store into pointer of base class
    Action* pAction = new ActionCreateServer(id, capacity, name, manager, std::move(function));
    return pAction;
}

Action *ActionMaker::makeJoinAction(std::vector<uint8_t> &data, GameManager &manager,
                                    std::function<void(BlockingQueue<Action *> *,
                                                       BlockingQueue<Action *> *)> function) {
    uint8_t id(data[0]);
    std::string name(data.begin()+1,data.end());
    //strip last spaces from name
    std::string stripped = name.substr(0, name.find_last_of(' '));
//    std::shared_ptr<Action> pAction = std::make_shared<ActionJoinServer>(id,name);
//    std::unique_ptr<Action> pAction(new ActionJoinServer(id, name));
    // create pointer to derived class and store into pointer of base class
    Action* pAction = new ActionJoinServer(id, stripped, manager , std::move(function));
    return pAction;
}

Action *ActionMaker::makeListAction(std::vector<uint8_t> &vector, GameManager &manager,
                                    std::function<void(BlockingQueue<Action *> *,
                                                       BlockingQueue<Action *> *)> function) {
    Action* pAction = new ActionListServer(0, manager, std::move(function));
    return pAction;
}

Action *ActionMaker::makeUpdateAction(std::vector<uint8_t> &vector) {
    return nullptr;
}
