//
// Created by lucaswaisten on 13/11/22.
//

#include "QueueIsEmptyException.h"

#include <utility>

QueueIsEmptyException::QueueIsEmptyException(std::string msg, ...) noexcept : msg_Error(std::move(msg)) {}

const char *QueueIsEmptyException::what() const noexcept {
    return exception::what();
}


