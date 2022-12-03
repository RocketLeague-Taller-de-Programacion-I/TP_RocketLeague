//
// Created by lucaswaisten on 29/11/22.
//
#include <catch2/catch_test_macros.hpp>
#include <functional>
#include "MockServerProtocol.h"
#include "sub_server/ServerProtocolo.h"

/*
 * Test unitario de protocolo
 *      - Buscaremos testiar cuando recibe mensajes desde cliente
 *      y los mismos se serializan en comandos de 2 bytes.
 *      - Buscaremos testiar las respuestas del servidor
 *      los casos exitosos y los casos no exitosos.
 * recibir:
      - createACK -> {type, id, returnCode}
      - joinACK -> {type, id, returnCode}
      - listACK -> {type, id, returnCode, cantidadDeGames = 2 , [online, max, size, name] , [online, max, size, name]}
      - worldACK -> {ballX, ballY, localScore, visitScore, n_clients, [id,x_pos,y_pox,angleSing,angle, ... for each client]}
 */

MockServerProtocol mockCreateOK(1,1,"test");
MockServerProtocol mockCreateERROR(1,ERROR_FULL);

TEST_CASE("ServerProtocol can deserialize create action", "[severProtocol]") {
    uint8_t id = 1;
    SECTION("CreateAction with return code OK") {
        std::function<void(std::vector<uint8_t> &, uint8_t &)> bytes_receiver_callable =
                [](std::vector<uint8_t> &toRead, uint8_t &size) { mockCreateOK.receiveBytes(toRead, size); };

        auto action = ServerProtocolo::deserializeData(id, CREATE_ACK,
                                                       bytes_receiver_callable);

        REQUIRE(action->getId() == 1);
    }
}