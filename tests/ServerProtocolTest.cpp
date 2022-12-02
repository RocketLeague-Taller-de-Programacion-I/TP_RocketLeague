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

/*
 * Defino los mock a utilizar en CreactACK
 * mockCreateOK
 *      atributos:
 *          - id = 1
 *          - retunCode = OK;
 * mockCreateERROR
 *      atributos:
 *          - id = 1
 *          - retunCode = ERROR_FULL;
 */
MockServerProtocol mockCreateOK(1,OK);
MockServerProtocol mockCreateERROR(1,ERROR_FULL);

TEST_CASE("ClientProtocol can deserialize CreateACK update", "[clientProtocol]") {
    uint8_t id = 1;
    SECTION("CreateACK with return code OK") {
        std::function<void(std::vector<uint8_t> &, uint8_t &)> bytes_receiver_callable =
                [](std::vector<uint8_t> &retuncode, uint8_t &size) { mockCreateOK.receiveBytes(retuncode, size); };

        auto action = Protocolo::deserializeData(id, CREATE_ACK,
                                                      bytes_receiver_callable);

        REQUIRE(action->getId() == 1);
    }
    SECTION("CreateACK with return code ERROR") {
        std::function<void(std::vector<uint8_t> &, uint8_t &)> bytes_receiver_callable =
                [](std::vector<uint8_t> &retuncode, uint8_t &size) { mockCreateOK.receiveBytes(retuncode, size); };

        auto action = Protocolo::deserializeData(id, CREATE_ACK,
                                                 bytes_receiver_callable);

        REQUIRE(action->getId() == 1);
    }
}
/*
 * Defino los mock a utilizar en JoinACK
 * mockJoinOK
 *      atributos:
 *          - id = 1
 *          - retunCode = OK;
 * mockJoinERROR
 *      atributos:
 *          - id = 1
 *          - retunCode = ERROR_FULL;
 */
MockServerProtocol mockJoinOK(1,OK);
MockServerProtocol mockJoinERROR(1,ERROR_FULL);

TEST_CASE("ClientProtocol can deserialize JoinACK update", "[clientProtocol]") {
    uint8_t id = 1;
    SECTION("JoinACK with return code OK") {
        std::function<void(std::vector<uint8_t> &, uint8_t &)> bytes_receiver_callable =
                [](std::vector<uint8_t> &retuncode, uint8_t &size) { mockCreateOK.receiveBytes(retuncode, size); };

        auto update = Protocolo::deserializeData(id,JOIN_ACK,
                                                      bytes_receiver_callable);

        REQUIRE(update->getId() == 1);

    }
    SECTION("JoinACK with return code ERROR") {
        std::function<void(std::vector<uint8_t> &, uint8_t &)> bytes_receiver_callable =
                [](std::vector<uint8_t> &retuncode, uint8_t &size) { mockCreateOK.receiveBytes(retuncode, size); };

        auto update = Protocolo::deserializeData(id,JOIN_ACK,
                                                      bytes_receiver_callable);

        REQUIRE(update->getId() == 1);
    }
}
/*
 * Defino los mock a utilizar en JoinACK
 * mockListOK
 *      atributos:
 *          - id = 1
 *          - retunCode = OK
 *          - cantGame = 1
 *          - online = 1
 *          - capacity = 2
 *          - sizeName = 4
 *          - name = "test"
 * mockListERROR
 *      atributos:
 *          - id = 1
 *          - retunCode = ERROR_FULL
 */
std::vector<uint8_t> dataList = {1, OK, 1, 1, 2, 4,};
//MockClientProtocol mockListOK(1, OK, 1, 1, 2, 4, "test");
MockServerProtocol mockListOK(dataList,"test");
MockServerProtocol mockListERROR(1,ERROR_FULL);

TEST_CASE("ClientProtocol can deserialize ListACK update", "[clientProtocol]") {
    uint8_t id = 1;
    SECTION("ListACK with return code OK and has one ") {
        std::function<void(std::vector<uint8_t> &, uint8_t &)> bytes_receiver_callable =
                [](std::vector<uint8_t> &retuncode, uint8_t &size) { mockCreateOK.receiveBytes(retuncode, size); };

        auto update = Protocolo::deserializeData(id,LIST_INFO,
                                                      bytes_receiver_callable);

        REQUIRE(update->getId() == 1);
    }

    SECTION("ListACK with return code ERROR")  {
        std::function<void(std::vector<uint8_t> &, uint8_t &)> bytes_receiver_callable =
                [](std::vector<uint8_t> &retuncode, uint8_t &size) { mockCreateOK.receiveBytes(retuncode, size); };

        auto update = Protocolo::deserializeData(id,LIST_INFO,
                                                      bytes_receiver_callable);

        REQUIRE(update->getId() == 1);
    }
}
/*
 * Defino los mock a utilizar en JoinACK
 * mockListOK
 *      atributos:
 *          - ballX = 0
 *          - ballY = 0
 *          - score_local = 0
 *          - score_visit = 0
 *          - n_clients = 1
 *          - id = 1
 *          - x_pos = 100
 *          - y_pos = 200
 *          - angleSign = 0
 *          - angle = 60
 * mockListERROR
 *      atributos:
 *          - id = 1
 *          - retunCode = ERROR_FULL
 */
std::vector<uint16_t> dataTestOne = {2000, 3000, 2, 0, 1, 1, 0, 0, 0, 0};
MockServerProtocol mockWorldOneOK(dataTestOne);
std::vector<uint16_t> dataTestTwo = {0, 0, 0, 0, 1, 1, 2000, 4000, 0, 60};
MockServerProtocol mockWorldTwoOK(dataTestTwo);

TEST_CASE("ClientProtocol can deserialize WorldACK update", "[clientProtocol]") {
    uint8_t id = 1;
    SECTION("Update WorldACK with ball in position (0,0) and score (0,0)") {
        std::function<void(std::vector<uint8_t> &, uint8_t &)> bytes_receiver_callable =
                [](std::vector<uint8_t> &retuncode, uint8_t &size) { mockCreateOK.receiveBytes(retuncode, size); };

        auto update = Protocolo::deserializeData(id,WORLD,
                                                      bytes_receiver_callable);

    }

    SECTION("Update WorldACK with car in position (200,400) and angle 60 degrees") {
        std::function<void(std::vector<uint8_t> &, uint8_t &)> bytes_receiver_callable =
                [](std::vector<uint8_t> &retuncode, uint8_t &size) { mockCreateOK.receiveBytes(retuncode, size); };

        auto update = Protocolo::deserializeData(id,WORLD,
                                                      bytes_receiver_callable);
    }
}

TEST_CASE("ClientProtocol receive an non-existed command", "[clientProtocol]") {
    uint8_t id = 1;
    std::function<void(std::vector<uint8_t> &, uint8_t &)> bytes_receiver_callable =
            [](std::vector<uint8_t> &retuncode, uint8_t &size) { mockCreateOK.receiveBytes(retuncode, size); };

    auto update = Protocolo::deserializeData(id, -1,bytes_receiver_callable);
    REQUIRE(update == nullptr);
}