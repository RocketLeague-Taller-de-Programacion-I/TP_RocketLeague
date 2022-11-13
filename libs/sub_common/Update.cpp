//
// Created by lucaswaisten on 12/11/22.
//

#include <utility>
#include <string>
#include "Update.h"

Update::Update(std::string aData) : data(std::move(aData)) {}
