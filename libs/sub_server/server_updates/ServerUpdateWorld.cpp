#include "ServerUpdateWorld.h"
#include "sub_server/ServerProtocolo.h"

uint8_t ServerUpdateWorld::getType() const {
    return WORLD;
}

void
ServerUpdateWorld::beSerialized(ServerProtocolo *protocolo, std::function<void(void *, unsigned int)> &sendCallable) {
    protocolo->serializeWorldUpdate(this, sendCallable);
}
