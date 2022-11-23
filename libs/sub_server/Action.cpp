//
// Created by lucaswaisten on 12/11/22.
//

#include "Action.h"
#include "gameManager.h"
#include <utility>

Action::Action() : idCreator(0),
                    capacityGame(0),
                    nameGame("") {}

Action::Action(uint8_t &id,
               uint8_t &c,
               std::string name) :
               idCreator(id),
               capacityGame(c),
               nameGame(std::move(name)) {}

std::string Action::getGameName() {
    return std::string();
}

uint8_t Action::getCapacity() {
    return 0;
}

uint8_t Action::getIdCreatorGame() {
    return 0;
}

std::uint8_t Action::getType() const {
    return 0;
}

void Action::execute(GameManager &manager,const std::function<void(BlockingQueue<Action *> *, BlockingQueue<Action *> *)> &setQueue) {}

Action::Action(uint8_t &id, std::string name) : idCreator(id),
                                                capacityGame(0),
                                                nameGame(std::move(name)) {}

std::vector<uint8_t> Action::beSerialized() {
    return std::vector<uint8_t>();
}

std::string Action::getNameGame() const {
    return nameGame;
}

Action::~Action() = default;


