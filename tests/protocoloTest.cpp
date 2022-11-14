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
          "[single-file]" ) {
    /*
    * protocolo.getMapCommand recibe una serie de acciones
    * en formato string y devuelve un comando serializado
    */
    SECTION("Accion JUMP") {
        REQUIRE(
                protocolo.getMapCommand(SDLK_SPACE)
                == JUMP_C);
    }
    SECTION("Accion RIGHT") {
        REQUIRE(
                protocolo.getMapCommand(SDLK_RIGHT)
                == RIGHT_C);
    }
    SECTION("Accion LEFT") {
        REQUIRE(
                protocolo.getMapCommand(SDLK_LEFT)
                == LEFT_C);
    }
    SECTION("Accion UP") {
        REQUIRE(
                protocolo.getMapCommand(SDLK_UP)
                == UP_C);
    }

    SECTION("Accion TURBO") {
        REQUIRE(
                protocolo.getMapCommand(SDLK_KP_C)
                == TURBO_C);
    }
    SECTION("Accion DOWN") {
        REQUIRE(
                protocolo.getMapCommand(SDLK_DOWN)
                == DOWN_C);
    }
}
TEST_CASE( "Protocolo serializa acciones de Menu", "[single-file]" ) {
    /*
     * las acciones de Menu, son las acciones de creacion de partida
     * listar games o unirse a una partida
     */
    SECTION("Accion CREATE") {

        REQUIRE(
                protocolo.getMapCommand(SDLK_0)
                == CREATE_C);
    }
    SECTION("Accion LIST") {

        REQUIRE(
                protocolo.getMapCommand(SDLK_1)
                == LIST_C);
    }
    SECTION("Accion JOIN") {

        REQUIRE(
                protocolo.getMapCommand(SDLK_2)
                == JOIN_C);
    }
}