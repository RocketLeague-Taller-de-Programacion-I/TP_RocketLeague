//
// Created by roby on 24/11/22.
//

#include "ListACK.h"

ListACK::ListACK(uint8_t &id, std::string &list) : GameUpdate(id, list) {}

// TODO: a mejorar que devuelve, capaz un map?
std::vector<std::string> ListACK::getList() {
    std::vector<std::string> vec;
    std::string delimiter = ",";
    size_t pos = 0;
    std::string token;
    while((pos = data.find(delimiter)) != std::string::npos) {
        token = data.substr(0, pos);
        vec.push_back(token);
        data.erase(0, pos + delimiter.length());
    }
    return vec;
}
