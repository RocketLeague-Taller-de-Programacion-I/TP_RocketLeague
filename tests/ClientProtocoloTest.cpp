//
// Created by lucaswaisten on 04/11/22.
//
#include <catch2/catch_test_macros.hpp>
#include "sub_client/ClientProtocol.h"


class MockClientProtocol {
public:
    MockClientProtocol(uint8_t &i, bool &b) : id(i),returncode(b) {}
    void receiveByteAndReturnCodeOK(void *bytes_to_read, int size) {
        auto * pbytes_to_read = (uint8_t *) bytes_to_read;
        returncode ?  *pbytes_to_read = 0 : *pbytes_to_read = id;
        returncode = true;
    }
    void returnCodeError(void *bytes_to_read, int size) {
        auto * pbytes_to_read = (uint8_t *) bytes_to_read;
        returncode ?  *pbytes_to_read = 1 : *pbytes_to_read = id;
        returncode = true;
    }
private:
    uint8_t &id;
    bool returncode;
};

uint8_t id = 1;
bool returnCode = false;
MockClientProtocol mock(id,returnCode);

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
                [](void * retuncode, int size) { mock.receiveByteAndReturnCodeOK(retuncode,size); };

        auto update = ClientProtocol::deserializeData(CREATE_ACK,
                                                      bytes_receiver_callable);

        REQUIRE(update->getId() == 1);
        REQUIRE(update->getReturnCode() == OK);
    }
    SECTION("CreateACK with return code ERROR") {
        std::function<void(void *, int)> bytes_receiver_callable =
                [](void * retuncode, int size) { mock.returnCodeError(retuncode,size); };
        auto update = ClientProtocol::deserializeData(CREATE_ACK,
                                                      bytes_receiver_callable);
        REQUIRE(update->getId() == 1);
        REQUIRE(update->getReturnCode() == ERROR_FULL);
    }
}
/*

TEST_CASE("ClientProtocol can deserialize JoinACK update", "[clientProtocol]") {
    std::vector<uint8_t> data;
    data.emplace_back(JOIN_ACK);
    data.emplace_back(1); //id

    SECTION("JoinACK with return code OK") {
        data.emplace_back(0); //return code
        ClientUpdate *update = clientProtocol.deserializeData(data);
        REQUIRE(update->getId() == 1);
        REQUIRE(update->getReturnCode() == OK);
    }

    SECTION("JoinACK with return code ERROR") {
        data.emplace_back(1); //return code
        ClientUpdate *update = clientProtocol.deserializeData(data);
        REQUIRE(update->getId() == 1);
        REQUIRE(update->getReturnCode() == ERROR_FULL);
    }
}

TEST_CASE("ClientProtocol can deserialize ListACK update", "[clientProtocol]") {
    std::vector<uint8_t> data;
    data.emplace_back(LIST_INFO);
    data.emplace_back(1); //id

    SECTION("ListACK with return code ERROR")  {
        data.emplace_back(1); //return code
        ClientUpdate *update = clientProtocol.deserializeData(data);
        REQUIRE(update->getId() == 1);
        REQUIRE(update->getReturnCode() == ERROR_FULL);
    }

    SECTION("ListACK with return code OK and has one ") {
        data.emplace_back(0); //return code
        data.emplace_back(1); //cantidad de games
        data.emplace_back(1); //online
        data.emplace_back(2); //max
        std::string name = "test";
        data.emplace_back(name.length()); //size
        data.insert(data.end(), name.begin(), name.end()); //name
        ClientListACK *update = (ClientListACK *) clientProtocol.deserializeData(data);
        REQUIRE(update->getId() == 1);
        REQUIRE(update->getReturnCode() == OK);
        REQUIRE(update->getList()[0].length() == name.length());
    }
}*/
