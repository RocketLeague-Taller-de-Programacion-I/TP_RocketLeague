//
// Created by lucaswaisten on 12/11/22.
//

#include <utility>
#include <string>
#include "Update.h"

Update::Update(const uint8_t &type,
               std::vector<uint8_t> &data) : Information(type,data){}
