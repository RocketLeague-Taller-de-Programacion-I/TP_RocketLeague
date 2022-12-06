#include "ServerUpdateStats.h"
#include "sub_server/ServerProtocolo.h"

uint8_t ServerUpdateStats::getType() const {
    return GAME_OVER;
}

void
ServerUpdateStats::beSerialized(ServerProtocolo *protocolo, std::function<void(void *, unsigned int)> &sendCallable) {
    protocolo->serializeStatsUpdate(this, sendCallable);
}
