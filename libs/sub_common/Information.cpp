//
// Created by lucaswaisten on 13/11/22.
//

#include "Information.h"

#include <utility>
#include <string>


Information::Information(uint8_t aType,
                         std::vector<char> aData) :
                         type(aType),
                         data(std::move(aData)) {}


