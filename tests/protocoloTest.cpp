//
// Created by lucaswaisten on 01/11/22.
//
#include <catch2/catch_test_macros.hpp>
#include "../sub_common/protocolo.h"

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
    * protocolo.serializeAction recibe una serie de acciones
    * en formato string y devuelve un comando serializado
    */
    SECTION("Accion JUMP") {
        REQUIRE(
                protocolo.serializeAction("jump")
                == JUMP);
    }
    SECTION("Accion RIGHT") {
        REQUIRE(
                protocolo.serializeAction("right")
                == RIGHT);
    }
    SECTION("Accion LEFT") {
        REQUIRE(
                protocolo.serializeAction("left")
                == LEFT);
    }
    SECTION("Accion UP") {
        REQUIRE(
                protocolo.serializeAction("up")
                == UP);
    }

    SECTION("Accion TURBO") {
        REQUIRE(
                protocolo.serializeAction("turbo")
                == TURBO);
    }
    SECTION("Accion DOWN") {
        REQUIRE(
                protocolo.serializeAction("down")
                == DOWN);
    }
}
TEST_CASE( "Protocolo serializa acciones de Menu", "[single-file]" ) {
    /*
     * las acciones de Menu, son las acciones de creacion de partida
     * listar partidas o unirse a una partida
     */
    SECTION("Accion CREATE") {

        REQUIRE(
                protocolo.serializeAction("create")
                == CREATE);
    }
    SECTION("Accion LIST") {

        REQUIRE(
                protocolo.serializeAction("list")
                == LIST);
    }
    SECTION("Accion JOIN") {

        REQUIRE(
                protocolo.serializeAction("join")
                == JOIN);
    }
}
