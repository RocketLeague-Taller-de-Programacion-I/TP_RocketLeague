//
// Created by lucaswaisten on 29/11/22.
//
#include "Catch2/src/catch2/catch_test_macros.hpp"
#include <functional>
#include "sub_server/ServerProtocolo.h"
#include "sub_server/gameManager.h"
#include "MockMoveProtocol.h"
#include "MockActionProtocol.h"
#include "MockUpdateProtocol.h"
#include "MockUpdateWorldProtocol.h"

/*
 * Test unitario de protocolo
 *      - Se testea la deserialziacion de la data en una Action.
 *      - Se testea la serializacion de la action a data.
 */

MockActionProtocol mockCreate(2, "test");

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

MockActionProtocol mockJoin("testJoin");
TEST_CASE("ServerProtocol can deserialize join action", "[serverProtocol]") {
    uint8_t id = 4,type=JOIN_ROOM;
    GameManager manager;
    SECTION("JoinAction with return code OK") {
        std::function<void(void *, int)> bytes_receiver_callable =
                [](void *toRead, int size) { mockJoin.receiveBytes(toRead, size); };

        auto action =  std::reinterpret_pointer_cast<ServerJoinRoom>(ServerProtocolo::deserializeDataOnCommand(type,
                                                                                                                 id,
                                                                                                                 manager,
                                                                                                                 bytes_receiver_callable));

        REQUIRE(action->getId() == 4);
        REQUIRE(action->getRoomName() == "testJoin");
    }
}

MockActionProtocol mockList;
TEST_CASE("ServerProtocol can deserialize list action", "[serverProtocol]") {
    uint8_t id = 2,type=LIST_ROOMS;
    GameManager manager;
    SECTION("ListAction with return code OK") {
        std::function<void(void *, int)> bytes_receiver_callable =
                [](void *toRead, int size) { mockList.receiveBytes(toRead, size); };

        auto action =  std::reinterpret_pointer_cast<ServerListRooms>(ServerProtocolo::deserializeDataOnCommand(type,
                                                                                                                 id,
                                                                                                                 manager,
                                                                                                                 bytes_receiver_callable));
        REQUIRE(action->getId() == 2);
    }
}

MockMoveProtocol mockMove(1,2,0);

TEST_CASE("ServerProtocol can deserialize move action", "[serverProtocol]") {
    uint8_t id = 2,type=MOVE;
    GameManager manager;
    SECTION("ListAction with return code OK") {
        std::function<void(void *, int)> bytes_receiver_callable =
                [](void *toRead, int size) { mockMove.receiveData(toRead, size); };

        auto action = ServerProtocolo::deserializeData(
                bytes_receiver_callable);
        REQUIRE(action->getId() == 1);
    }
}

/*
 * SERIALIZE TEST
 */

MockUpdateProtocol mock;
std::function<void(void *, unsigned int)> sendBytes =
        [](void * retuncode, unsigned int size) { mock.sendBytes(retuncode,size); };
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

MockUpdateWorldProtocol mockWorld;
std::vector<int> data = {10,10,3,2,1,
                         1,10,10,60,1,
                         2,10,10,60,1,};
std::function<void(void *, unsigned int)> sendBytesWorld =
        [](void * retuncode, unsigned int size) { mockWorld.sendBytes(retuncode,size); };

TEST_CASE("ServerProtocol serialize WordlACK update","[serverProtocol]"){
    std::shared_ptr<ServerUpdate> update = std::make_shared<ServerUpdateWorld>(data);

    serverProtocol.serializeUpdate(update,sendBytesWorld);

    REQUIRE( mockWorld.ballPosition() == 10);
    REQUIRE(mockWorld.ballPosition() == 10);
    REQUIRE(mockWorld.getScoreLocal() == 3);
    REQUIRE(mockWorld.getScoreVisitor() == 2);
    REQUIRE(mockWorld.getTime() == 1);
}

