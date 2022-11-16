//
// Created by franco on 24/10/22.
//

#include <iostream>
#include "sub_server/Server.h"
//  Cada vez que queramos hacer include de box2d
#include "box2d/box2d.h"
#include "sub_server/Car.h"
#include "sub_server/Match.h"

int main(int argc, char const *argv[])
{
    std::string partida = "partida";
    Match match(partida, 5);
    std::string name = "franco";
    match.addPlayer(name);
}
