
#include "ActionListRooms.h"
#include "sub_client/ClientProtocol.h"

void ActionListRooms::beSerialized(ClientProtocol *protocolo) {
    protocolo->serializeListRooms(this);
}

uint8_t ActionListRooms::getType() const {
    return LIST;
}
