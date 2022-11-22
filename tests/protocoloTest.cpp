//
// Created by lucaswaisten on 04/11/22.
//
#include <catch2/catch_test_macros.hpp>
#include <SDL2/SDL_keycode.h>
#include "sub_common/protocolo.h"


/*
 * Defino de forma global a protocolo que utilizare para los test.
 */
Protocolo protocolo;
/*
 * Test unitario de protocolo
 *      - Buscaremos testiar cuando recibe mensajes desde cliente
 *      y los mismos se serializan en comandos de 2 bytes.
 *      - Buscaremos testiar las respuestas del servidor
 *      los casos exitosos y los casos no exitosos.
 */

TEST_CASE("Protocolo serializa acciones del jugador",
          "[Protocolo]" ) {
    /*
    * protocolo.getMapCommand recibe una serie de acciones
    * en formato string y devuelve un comando serializado
    */
    SECTION("Accion JUMP") {
        REQUIRE(
                protocolo.getMapCommand(SDLK_SPACE)
                == JUMP);
    }
    SECTION("Accion RIGHT") {
        REQUIRE(
                protocolo.getMapCommand(SDLK_RIGHT)
                == RIGHT);
    }
    SECTION("Accion LEFT") {
        REQUIRE(
                protocolo.getMapCommand(SDLK_LEFT)
                == LEFT);
    }
    SECTION("Accion UP") {
        REQUIRE(
                protocolo.getMapCommand(SDLK_UP)
                == UP);
    }

    SECTION("Accion TURBO") {
        REQUIRE(
                protocolo.getMapCommand(SDLK_t)
                == TURBO);
    }
    SECTION("Accion DOWN") {
        REQUIRE(
                protocolo.getMapCommand(SDLK_DOWN)
                == DOWN);
    }
}
TEST_CASE( "Protocolo serializa acciones de Menu", "[Protocolo]" ) {
    /*
     * las acciones de Menu, son las acciones de creacion de partida
     * listar games o unirse a una partida
     */
    SECTION("Accion CREATE") {

        REQUIRE(
                protocolo.getMapCommand(SDLK_0)
                == CREATE_ROOM);
    }
    SECTION("Accion LIST") {

        REQUIRE(
                protocolo.getMapCommand(SDLK_1)
                == LIST_ROOMS);
    }
    SECTION("Accion JOIN") {

        REQUIRE(
                protocolo.getMapCommand(SDLK_2)
                == JOIN_ROOM);
    }
}