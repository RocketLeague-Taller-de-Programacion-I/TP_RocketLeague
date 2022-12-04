//
// Created by lucaswaisten on 29/11/22.
//
#include <catch2/catch_test_macros.hpp>
#include <functional>
#include "MockServerProtocol.h"
#include "sub_server/ServerProtocolo.h"
#include "sub_server/gameManager.h"

/*
 * Test unitario de protocolo
 *      - Se testea la deserialziacion de la data en una Action.
 *      - Se testea la serializacion de la action a data.
 */

MockServerProtocol mockCreate(2, "test");

TEST_CASE("ServerProtocol can deserialize create action", "[serverProtocol]") {
    uint8_t id = 1,type=CREATE_ROOM;
    GameManager manager;

    SECTION("CreateAction with return code OK") {
        std::function<void(void *, int)> bytes_receiver_callable =
                [](void *toRead, int size) { mockCreate.receiveBytes(toRead, size); };

        auto action =  std::reinterpret_pointer_cast<ServerCreateRoom>(ServerProtocolo::deserializeDataOnCommand(type,
                                                                                                                 id,
                                                                                                                 manager,
                                                                                                                 bytes_receiver_callable));

        REQUIRE(action->getId() == 1);
        REQUIRE(action->getRoomName() == "test");
        REQUIRE(action->getCapacity() == 2);
    }
}

MockServerProtocol mockJoin( "testJoin");
TEST_CASE("ServerProtocol can deserialize join action", "[serverProtocol]") {
    uint8_t id = 4,type=JOIN_ROOM;
    GameManager manager;
    SECTION("JoinAction with return code OK") {
        std::function<void(void *, int)> bytes_receiver_callable =
                [](void *toRead, int size) { mockJoin.receiveBytes(toRead, size); };

        auto action =  std::reinterpret_pointer_cast<ServerCreateRoom>(ServerProtocolo::deserializeDataOnCommand(type,
                                                                                                                 id,
                                                                                                                 manager,
                                                                                                                 bytes_receiver_callable));

        REQUIRE(action->getId() == 4);
        REQUIRE(action->getRoomName() == "testJoin");
    }
}

MockServerProtocol mockList;
TEST_CASE("ServerProtocol can deserialize list action", "[serverProtocol]") {
    uint8_t id = 2,type=JOIN_ROOM;
    GameManager manager;
    SECTION("ListAction with return code OK") {
        std::function<void(void *, int)> bytes_receiver_callable =
                [](void *toRead, int size) { mockList.receiveBytes(toRead, size); };

        auto action =  std::reinterpret_pointer_cast<ServerCreateRoom>(ServerProtocolo::deserializeDataOnCommand(type,
                                                                                                                 id,
                                                                                                                 manager,
                                                                                                                 bytes_receiver_callable));

        REQUIRE(action->getId() == 2);
    }
}

/*
 * SERIALIZE TEST
 */

MockServerProtocol mock;
std::function<void(void *, unsigned int)> sendBytes =
        [](void * retuncode, unsigned int size) { mock.sendBytesMock(retuncode,size); };
std::function<void(void *, unsigned int)> sendBytesWorld =
        [](void * retuncode, unsigned int size) { mock.sendBytesMockWorld(retuncode,size); };
ServerProtocolo serverProtocol;

TEST_CASE("ServerProtocol serialize CreateACK update","[serverProtocol]"){
    uint8_t id = 1, retunCode = OK;

    std::shared_ptr<ServerUpdate> update = std::make_shared<ServerCreateACK>(id,retunCode);

    serverProtocol.serializeUpdate(update,sendBytes);
    REQUIRE(mock.getType() == CREATE_ACK);
    REQUIRE(mock.getId() == id);
    REQUIRE(mock.getRetunCode() == OK);
}

TEST_CASE("ServerProtocol serialize JoinACK update","[serverProtocol]"){
    uint8_t id = 1, retunCode = OK;

    std::shared_ptr<ServerUpdate> update = std::make_shared<ServerJoinACK>(id,retunCode);

    serverProtocol.serializeUpdate(update,sendBytes);
    REQUIRE(mock.getType() == JOIN_ACK);
    REQUIRE(mock.getId() == id);
    REQUIRE(mock.getRetunCode() == OK);
}
std::vector<uint8_t> returnData = {1,1,1,10,10};

TEST_CASE("ServerProtocol serialize ListACK update","[serverProtocol]"){
    uint8_t id = 1, retunCode = OK, numberGame=2;

    std::shared_ptr<ServerUpdate> update = std::make_shared<ServerListACK>(id,retunCode,numberGame,returnData);

    serverProtocol.serializeUpdate(update,sendBytes);
    REQUIRE(mock.getType() == LIST_INFO);
    REQUIRE(mock.getId() == id);
    REQUIRE(mock.getRetunCode() == OK);
}
std::vector<int> data = {0,0,2,3,2,
                         1,10,10,60,1,
                         2,10,10,60,1,};
TEST_CASE("ServerProtocol serialize WordlACK update","[serverProtocol]"){
    std::shared_ptr<ServerUpdate> update = std::make_shared<ServerUpdateWorld>(data);

    serverProtocol.serializeUpdate(update,sendBytesWorld);

    REQUIRE(mock.ballPosition() == 0);
    REQUIRE(mock.ballPosition() == 0);
    REQUIRE(mock.getScoreLocal() == 2);
    REQUIRE(mock.getScoreVisitor() == 3);
}

