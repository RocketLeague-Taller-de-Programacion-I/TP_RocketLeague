//
// Created by franco on 21/11/22.
//

#ifndef ROCKETLEAGUE_ACTIONUPDATESCORE_H
#define ROCKETLEAGUE_ACTIONUPDATESCORE_H
#include "ActionUpdate.h"


class ActionUpdateScore : public ActionUpdate {
public:
    ActionUpdateScore(uint8_t& id, int &local, int &visit);
    ~ActionUpdateScore() override;
    int getLocal();
    int getVisit();
private:
    int local;
    int visit;
};

#endif //ROCKETLEAGUE_ACTIONUPDATESCORE_H
