
#include "ServerListACK.h"
#include "sub_server/ServerProtocolo.h"

void ServerListACK::beSerialized(ServerProtocolo *protocolo, std::function<void(void *, unsigned int)> &sendCallable) {
    protocolo->serializeServerListACK(this, sendCallable);
}

uint8_t ServerListACK::getType() const {
    return LIST_INFO;
}
