//
// Created by lucaswaisten on 31/10/22.
//

#include <string>
#include "protocolo.h"

Protocolo::Protocolo(const std::string &servname) :
                    socket(servname.c_str()) {}

Protocolo::Protocolo(const std::string &hostname,
                     const std::string &servname) :
                     socket(hostname.c_str(),
                            servname.c_str()) {}
