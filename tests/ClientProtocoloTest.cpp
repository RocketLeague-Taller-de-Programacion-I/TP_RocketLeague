//
// Created by lucaswaisten on 04/11/22.
//
#include <catch2/catch_test_macros.hpp>
#include <queue>
#include "sub_client/ClientProtocol.h"
#include "MockClientProtocol.h"

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
MockClientProtocol mockCreateOK(1,OK);
MockClientProtocol mockCreateERROR(1,ERROR_FULL);

TEST_CASE("ClientProtocol can deserialize CreateACK update", "[clientProtocol]") {

    SECTION("CreateACK with return code OK") {
        std::function<void(void *, int)> bytes_receiver_callable =
                [](void * retuncode, int size) { mockCreateOK.receiveBytes(retuncode, size); };

        auto update = ClientProtocol::deserializeData(CREATE_ACK,
                                                      bytes_receiver_callable);

        REQUIRE(update->getId() == 1);
        REQUIRE(update->getReturnCode() == OK);
        REQUIRE(update->getType() == CREATE_ACK);
    }
    SECTION("CreateACK with return code ERROR") {
        std::function<void(void *, int)> bytes_receiver_callable =
                [](void * retuncode, int size) { mockCreateERROR.receiveBytes(retuncode,size); };

        auto update = ClientProtocol::deserializeData(CREATE_ACK,
                                                      bytes_receiver_callable);

        REQUIRE(update->getId() == 1);
        REQUIRE(update->getReturnCode() == ERROR_FULL);
        REQUIRE(update->getType() == CREATE_ACK);
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
MockClientProtocol mockJoinOK(1,OK);
MockClientProtocol mockJoinERROR(1,ERROR_FULL);

TEST_CASE("ClientProtocol can deserialize JoinACK update", "[clientProtocol]") {

    SECTION("JoinACK with return code OK") {
        std::function<void(void *, int)> bytes_receiver_callable =
                [](void * retuncode, int size) { mockJoinOK.receiveBytes(retuncode,size); };

        auto update = ClientProtocol::deserializeData(JOIN_ACK,
                                                      bytes_receiver_callable);

        REQUIRE(update->getId() == 1);
        REQUIRE(update->getReturnCode() == OK);
        REQUIRE(update->getType() == JOIN_ACK);
    }
    SECTION("JoinACK with return code ERROR") {
        std::function<void(void *, int)> bytes_receiver_callable =
                [](void * retuncode, int size) { mockJoinERROR.receiveBytes(retuncode,size); };

        auto update = ClientProtocol::deserializeData(JOIN_ACK,
                                                      bytes_receiver_callable);

        REQUIRE(update->getId() == 1);
        REQUIRE(update->getReturnCode() == ERROR_FULL);
        REQUIRE(update->getType() == JOIN_ACK);
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
MockClientProtocol mockListOK(dataList,"test");
MockClientProtocol mockListERROR(1,ERROR_FULL);

TEST_CASE("ClientProtocol can deserialize ListACK update", "[clientProtocol]") {

    SECTION("ListACK with return code OK and has one ") {
        std::function<void(void *, int)> bytes_receiver_callable =
                [](void * retuncode, int size) { mockListOK.receiveBytes(retuncode,size); };

        auto update = ClientProtocol::deserializeData(LIST_INFO,
                                                      bytes_receiver_callable);

        REQUIRE(update->getId() == 1);
        REQUIRE(update->getReturnCode() == OK);
        auto games = update->getList();
        REQUIRE( games.at("test") == "1/2");
    }

    SECTION("ListACK with return code ERROR")  {
        std::function<void(void *, int)> bytes_receiver_callable =
                [](void * retuncode, int size) { mockListERROR.receiveBytes(retuncode,size); };

        auto update = ClientProtocol::deserializeData(LIST_INFO,
                                                      bytes_receiver_callable);

        REQUIRE(update->getId() == 1);
        REQUIRE(update->getReturnCode() == ERROR_FULL);;
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
std::vector<uint8_t> dataWorld = {0, 0, 0, 0, 1, 1,100,200,0,60};
MockClientProtocol mockWorldOK(dataWorld,"");
//MockClientProtocol mockListERROR(1,ERROR_FULL);

TEST_CASE("ClientProtocol can deserialize WorldACK update", "[clientProtocol]") {

    SECTION("WorldACK with return data of render objetc") {
        std::function<void(void *, int)> bytes_receiver_callable =
                [](void * retuncode, int size) { mockListOK.receiveBytes(retuncode,size); };

        auto update = ClientProtocol::deserializeData(WORLD,
                                                      bytes_receiver_callable);
        auto ball = update->getBall();
        auto cars = update->getCars();
        REQUIRE(ball.getX() == 0);
        REQUIRE(ball.getY() == 0);
        REQUIRE(cars[0].getX() == 100);
        REQUIRE(cars[0].getX() == 200);
    }

   /* SECTION("WorldACK with return code ERROR")  {
        std::function<void(void *, int)> bytes_receiver_callable =
                [](void * retuncode, int size) { mockListERROR.receiveBytes(retuncode,size); };

        auto update = ClientProtocol::deserializeData(WORLD,
                                                      bytes_receiver_callable);

        REQUIRE(update->getId() == 1);
        REQUIRE(update->getReturnCode() == ERROR_FULL);;
    }*/

}