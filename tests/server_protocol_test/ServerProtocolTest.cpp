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
#include "MockStatsProtocol.h"

#define INVALID_TYPE -1
/*
 * TEST UNITARIOS DE PROTOCOLO SERVIDOR
 *
 *  - PRIMERA SECCION:
 *      - ServerProtocol deserialíza la data a travéz del método:
 *          ServerProtocolo::deserializeDataOnCommand para las
 *          acciones comunes que son:
 *          - Create
 *          - Join
 *          - List
 *
 *      - ServerProtocol deserialíza la data de los movimientos
 *          por medio del metodo:
 *          ServerProtocolo::deserializeData
 *
 *      - Ambos métodos reciben una callback:
 *          - function: callback que llama a un socket.
 *
 *      - Desde la callback se retorna la siguente data:
 *          - create -> {capacity, nameSize, name}
 *          - join -> {nameSize, name}
 *          - list -> {}
 *          - move -> {idPlayer, direction, state}
 */

MockActionProtocol mockCreate(2, "test");

TEST_CASE("ServerProtocol can deserialize create action", "[serverProtocol]") {
    uint8_t id = 1,type=CREATE_ROOM;
    GameManager manager;

    SECTION("Create action with id == 41and name 'test' ") {
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
    SECTION("Join action with id == 4 and name 'testJoin' ") {
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
    SECTION("List action with id == 2") {
        std::function<void(void *, int)> bytes_receiver_callable =
                [](void *toRead, int size) { mockList.receiveBytes(toRead, size); };

        auto action =  std::reinterpret_pointer_cast<ServerJoinRoom>(ServerProtocolo::deserializeDataOnCommand(type,
                                                                                                               id,
                                                                                                               manager,
                                                                                                               bytes_receiver_callable));
        REQUIRE(action->getId() == 2);
    }
}

MockMoveProtocol mockMove(1,2,0);

TEST_CASE("ServerProtocol can deserialize move action", "[serverProtocol]") {
    GameManager manager;
    SECTION("Move action") {
        std::function<void(void *, int)> bytes_receiver_callable =
                [](void *toRead, int size) { mockMove.receiveData(toRead, size); };

        auto action = ServerProtocolo::deserializeData(bytes_receiver_callable);

        REQUIRE(action->getId() == 1);
    }
}
/*
 * En caso de que reciba un comando inexistente, se retorna un puntero a null.
 */
TEST_CASE("ServerProtocol receive an non-existed command", "[serverProtocol]") {
    uint8_t id = 2,type=INVALID_TYPE ;
    GameManager manager;

    std::function<void(void *, int)> bytes_receiver_callable =
            [](void *toRead, int size) {};

    auto action = ServerProtocolo::deserializeDataOnCommand(type,
                                                            id,
                                                            manager,
                                                            bytes_receiver_callable);

    REQUIRE(action == nullptr);
}

/*
*  - SEGUNDA SECCIÓN:
*      - ClientProtocol serializa los updates mediante el método:
*          ClientProtocol::serializeUpdate
*      - El método recibe un parámetro:
*          - update: punto a UpdateServer.
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
std::vector<int> data = {10, // x_ball
                         10, // y_ball
                         0, // ball_sing_angle
                         30, // ball_angle
                         3, // score_local
                         2, // score_visitor
                         1, // time
                         1, // n_client
                         1, // id_player_1
                         10, // x_car_player_1
                         10, // y_car_player_1
                         1, // sing_angle_car_player_1
                         60, // angle_car_player_1
                         1, // facing_car_player_1
                         };
std::function<void(void *, unsigned int)> sendBytesWorld =
        [](void * retuncode, unsigned int size) { mockWorld.sendBytes(retuncode,size); };

TEST_CASE("ServerProtocol serialize WordlACK update","[serverProtocol]"){
    std::shared_ptr<ServerUpdate> update = std::make_shared<ServerUpdateWorld>(data);

    serverProtocol.serializeUpdate(update,sendBytesWorld);

    REQUIRE(mockWorld.ballPosition() == 10);
    REQUIRE(mockWorld.ballPosition() == 10);
    REQUIRE(mockWorld.getSign() == 0);
    REQUIRE(mockWorld.getAngleBall()== 30);
    REQUIRE(mockWorld.getScoreLocal() == 3);
    REQUIRE(mockWorld.getScoreVisitor() == 2);
    REQUIRE(mockWorld.getTime() == 1);
}
std::vector<int> stats = { 2, // numberOfPlayers
                              1, // id_player1
                              5, // score_player1
                              2, // id_player2
                              1, // score_player2
};

MockStatsProtocol mockStats;
std::function<void(void *, unsigned int)> sendBytesStatsMock =
        [](void * bytes, unsigned int size) { mockStats.sendBytesStatsMock(bytes,size); };
TEST_CASE("ServerProtocol serialize StatsACK update","[serverProtocol]"){

    std::shared_ptr<ServerUpdate> update = std::make_shared<ServerUpdateStats>(stats);

    serverProtocol.serializeUpdate(update,sendBytesStatsMock);

    REQUIRE(mockStats.getCantPlayer() == 2);

    /* Player one */

    REQUIRE(mockStats.getId() == 1);
    REQUIRE(mockStats.getScore() == 5);

    /* Player two*/

    REQUIRE(mockStats.getId() == 2);
    REQUIRE(mockStats.getScore() == 1);
}