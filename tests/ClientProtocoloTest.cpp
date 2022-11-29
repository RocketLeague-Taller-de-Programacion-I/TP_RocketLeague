//
// Created by lucaswaisten on 04/11/22.
//
#include <catch2/catch_test_macros.hpp>
#include <queue>
#include "sub_client/ClientProtocol.h"


class MockClientProtocol {
public:
    MockClientProtocol(uint8_t id, uint8_t returnCode) {
        data.push(id);
        data.push(returnCode);
    }

    MockClientProtocol(uint8_t id, uint8_t returnCode, uint8_t cantGame, uint8_t online, uint8_t capacity,
                       uint8_t sizeName, const std::string &name) {
        data.push(id);
        data.push(returnCode);
        data.push(cantGame);
        data.push(online);
        data.push(capacity);
        data.push(sizeName);
        for(auto & i : name){
            data.push(i);
        }
    }

    void receiveBytes(void *bytes_to_read, int size) {
        auto * pbytes_to_read = (uint8_t *) bytes_to_read;
        for (int i =0 ; i<size;i++){
            *pbytes_to_read = data.front() ;
            if (size > 1)  *pbytes_to_read++ ;
            data.pop();
        }

    }
private:
    std::queue<uint8_t> data;
};

MockClientProtocol mockCreateOK(1,0);
MockClientProtocol mockCreateERROR(1,1);
MockClientProtocol mockJoinOK(1,0);
MockClientProtocol mockJoinERROR(1,1);
MockClientProtocol mockListOK(1, 0, 1, 1, 2, 4, "test");
MockClientProtocol mockListERROR(1,1);

/*
 * Test unitario de protocolo
 *      - Buscaremos testiar cuando recibe mensajes desde cliente
 *      y los mismos se serializan en comandos de 2 bytes.
 *      - Buscaremos testiar las respuestas del servidor
 *      los casos exitosos y los casos no exitosos.
 */

//Client Protocolo
// recibir:
//      - createACK -> {type, id, returnCode}
//      - joinACK -> {type, id, returnCode}
//      - listACK -> {type, id, returnCode, cantidadDeGames = 2 , [online, max, size, name] , [online, max, size, name]}

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
