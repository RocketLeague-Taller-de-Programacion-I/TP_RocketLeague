//
// Created by lucaswaisten on 13/11/22.
//

#ifndef ROCKETLEAGUE_QUEUEISEMPTYEXCEPTION_H
#define ROCKETLEAGUE_QUEUEISEMPTYEXCEPTION_H


#include <exception>
#include <string>

class QueueIsEmptyException : public std::exception {
private:
    std::string msg_Error;
public:
    explicit QueueIsEmptyException(std::string msg,...) noexcept;
    const char *what() const noexcept override;
    ~QueueIsEmptyException() noexcept override = default;
};


#endif //ROCKETLEAGUE_QUEUEISEMPTYEXCEPTION_H
