//
// Created by lucaswaisten on 04/11/22.
//

#include "protocolo.h"

/*
 * Hilo de sender popea de la cola de acciones
        Llama protocolo(Action)
Protocolo serializa la acción
devuelve un vector de char
        Hilo de sender envía el vector de char

        command_t Protocolo::getMapCommand(Action action) {
//procesa la accion y devuelve un vector de char
}
command_t Protocolo::getCommand(uint32_t action) {
    return this->mapCommand.at(action);
}*/

command_t Protocolo::getMapCommand(uint32_t action) {
    return this->mapCommand.at(action);
}
