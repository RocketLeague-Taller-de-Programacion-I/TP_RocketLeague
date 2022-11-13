//
// Created by lucaswaisten on 12/11/22.
//

#include <utility>
#include <string>
#include "Update.h"

Update::Update(uint8_t aType,
               std::string aData) : Information(aType,
                                                std::vector<char>(aData.begin(),
                                                                  aData.end())) {}
