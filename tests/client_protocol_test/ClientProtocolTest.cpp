#include "Catch2/src/catch2/catch_test_macros.hpp"
#include "sub_client/ClientProtocol.h"
#include "MockACKProtocol.h"
#include "MockWorldProtocol.h"
#include "MockActionProtocol.h"

/*
 * TEST UNITARIOS DE PROTOCOLO CLIENTE
 *
 *  - PRIMERA SECCION:
 *      - ClientProtocol deserialíza la data a travéz del método:
 *          ClientProtocol::deserializeData(type,function)

 *      - El método recibe dos parámetros:
 *          - type: tipo de acción.
 *          - function: callback que llama a un socket.

 *      - Desde la callback se retorna la siguente data:
 *          - createACK -> {type, id, returnCode}
 *          - joinACK -> {type, id, returnCode}
 *          - listACK -> {type, id, returnCode,
 *                          cantidadDeGames = 2,
 *                          [online, max, size, name],
 *                          [online, max, size, name]}
 *          - worldACK -> {ballX,
 *                          ballY,
 *                          localScore,
 *                          visitScore,
 *                          n_clients,
 *                          [id,x_pos,
 *                          y_pox,
 *                          angleSing,angle,
 *                          ...
 *                          for each client
 *                          ]}
 */

#define INVALID_TYPE -1
/*
 * MockACKProtocol recibe dos parametros:
 *  - id
 *  - retunCode
 */
MockACKProtocol mockCreateOK(1, OK);
MockACKProtocol mockCreateERROR(2,ERROR_FULL);

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

        REQUIRE(update->getId() == 2);
        REQUIRE(update->getReturnCode() == ERROR_FULL);
        REQUIRE(update->getType() == CREATE_ACK);
    }
}

MockACKProtocol mockJoinOK(2,OK);
MockACKProtocol mockJoinERROR(1,ERROR_FULL);

TEST_CASE("ClientProtocol can deserialize JoinACK update", "[clientProtocol]") {

    SECTION("JoinACK with return code OK") {
        std::function<void(void *, int)> bytes_receiver_callable =
                [](void * retuncode, int size) { mockJoinOK.receiveBytes(retuncode,size); };

        auto update = ClientProtocol::deserializeData(JOIN_ACK,
                                                      bytes_receiver_callable);

        REQUIRE(update->getId() == 2);
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
 * MockACKProtocol recibe dos parametros:
 *  - data = [id,
 *            returnCode,
 *            cantGame,
 *            online,
 *            capacity,
 *            sizeName,
 *            name]
 *  - retunCode
 */
std::vector<uint8_t> dataOK = {1, OK, 1, 1, 2, 4,};
MockACKProtocol mockListOK(dataOK,"test");

std::vector<uint8_t> dataError = {1, ERROR_FULL, 1, 1, 2, 4,};
MockACKProtocol mockListERROR(dataError,"test");

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
        REQUIRE(update->getReturnCode() == ERROR_FULL);
    }
}
/*
 * MockWorldProtocol recibe por parametro:
 *  - data = [x_ball,
 *            y_ball,
 *            local,
 *            visitor,
 *            time,
 *            n_client,
 *            [player_data] = [id,
 *                             x_car,
 *                             y_car,
 *                             angle_sing,
 *                             angle,
 *                             facing_where]
 *
 *            ... for each `n_client`
 *            ]
 */

std::vector<uint16_t> dataTestOne = {10, // x_ball
                                     10, // y_ball
                                     1, // ball_angleSing
                                     15, // ball_angle
                                     2, // local
                                     0, // visitor
                                     1, // time
                                     1, // n_client
                                     2, // id_client1
                                     200, // x_car
                                     330, // y_car
                                     1, // angle_sing
                                     60,// angle
                                     0 // facing_where
                                        };
MockWorldProtocol mockWorldOneOK(dataTestOne);

std::vector<uint16_t> dataTestTwo = {20, // x_ball
                                     20, // y_ball
                                     1, // ball_angleSing
                                     20, // ball_angle
                                     3, // local
                                     2, // visitor
                                     5, // time
                                     1, // n_client
                                     3, // id_client1
                                     400, // x_car
                                     500, // y_car
                                     1, // car_angle_sing
                                     30,// car_angle
                                     1 // facing_where
};
MockWorldProtocol mockWorldTwoOK(dataTestTwo);

TEST_CASE("ClientProtocol can deserialize WorldACK update", "[clientProtocol]") {

    SECTION("Update WorldACK with dataTestOne") {
        std::function<void(void *, int)> bytes_receiver_callable =
                [](void * retuncode, int size) { mockWorldOneOK.receiveBytes(retuncode,size); };

        auto update = ClientProtocol::deserializeData(WORLD,bytes_receiver_callable);

        REQUIRE(update->getType() == WORLD);
        /*
         * Ball Assert
         */
        auto ball = update->getBall();
        auto x = (int)(ball.getX()*1000);
        auto y = (int)(ball.getY()*1000);
        auto ball_angle =  (int)(ball.getAngle()*1000);
        REQUIRE(x == 10);
        REQUIRE(y == 10);
        REQUIRE(ball_angle == 15);

        /*
         * Score Assert
         */
        auto score = update->getScore();

        REQUIRE(score.getLocal() == 2);
        REQUIRE(score.getVisitor() == 0);

        /*
         * Cars Assert
         */
        auto cars = update->getCars();

        auto x_car = (int)(cars[0].getX()*1000);
        auto y_car = (int)(cars[0].getY()*1000);
        auto angle  = (int) (cars[0].getAngle() * 1000);
        auto facing  = cars[0].getFacing();
        auto id = cars[0].getId();

        REQUIRE(id == 2);
        REQUIRE(x_car == 200);
        REQUIRE(y_car == 330);
        REQUIRE(angle == 60);
        REQUIRE(facing == 0);

        /*
         * Time Assert
         */
        auto gametime = update->getTime();
        auto time = gametime.getTime();
        REQUIRE(time == 1);
    }

    SECTION("Update WorldACK with dataTestOne") {
        std::function<void(void *, int)> bytes_receiver_callable =
                [](void * retuncode, int size) { mockWorldTwoOK.receiveBytes(retuncode,size); };

        auto update = ClientProtocol::deserializeData(WORLD,bytes_receiver_callable);

        REQUIRE(update->getType() == WORLD);
        /*
         * Ball Assert
         */
        auto ball = update->getBall();
        auto x = (int)(ball.getX()*1000);
        auto y = (int)(ball.getY()*1000);
        auto ball_angle = (int)(ball.getAngle()*1000);
        REQUIRE(x == 20);
        REQUIRE(y == 20);
        REQUIRE(ball_angle == 20);
        /*
         * Score Assert
         */
        auto score = update->getScore();

        REQUIRE(score.getLocal() == 3);
        REQUIRE(score.getVisitor() == 2);

        /*
         * Cars Assert
         */
        auto cars = update->getCars();

        auto x_car = (int)(cars[0].getX()*1000);
        auto y_car = (int)(cars[0].getY()*1000);
        auto angle  = (int) (cars[0].getAngle() * 1000);
        auto facing  = cars[0].getFacing();
        auto id = cars[0].getId();

        REQUIRE(id == 3);
        REQUIRE(x_car == 400);
        REQUIRE(y_car == 500);
        REQUIRE(angle == 30);
        REQUIRE(facing == 1);

        /*
         * Time Assert
         */
        auto gametime = update->getTime();
        auto time = gametime.getTime();
        REQUIRE(time == 5);
    }
}
std::vector<uint8_t> data = { 2, // numberOfPlayers
                              1, // id_player1
                              3, // score_player1
                              2, // id_player2
                              0, // score_player2
                              };
MockACKProtocol mockStat(data);

TEST_CASE("ClientProtocol can deserialize StatACK update", "[clientProtocol]") {

    SECTION("Update StatACK with data") {
        std::function<void(void *, int)> bytes_receiver_callable =
                [](void * retuncode, int size) { mockStat.receiveBytes(retuncode,size); };

        auto update = ClientProtocol::deserializeData(GAME_OVER,bytes_receiver_callable);

        REQUIRE(update->getType() == GAME_OVER);
        /*
         * Score Assert
         */
        auto stats = std::static_pointer_cast<ClientUpdateStats>(update)->getStats();
        REQUIRE(stats.at(1)==3);
        REQUIRE(stats.at(2)==0);
    }
}
/*
 * En caso de que reciba un comando inexistente, se retorna un puntero a null.
 */
TEST_CASE("ClientProtocol receive an non-existed command", "[clientProtocol]") {
    auto type = INVALID_TYPE;
    std::function<void(void *, int)> bytes_receiver_callable = [](void * retuncode, int size) { };

    auto update = ClientProtocol::deserializeData(type,
                                                  bytes_receiver_callable);

    REQUIRE(update == nullptr);
}

/*
*  - SEGUNDA SECCIÓN:
*      - ClientProtocol serializa la accién mediante el método:
*          ClientProtocol::serializeAction(action)
*      - El método recibe un parámetro:
*          - action: punto a ClientAction.
*/

/*
 * Defino de forma global a ClientProtocol y a MockActionProtocol que utilizare.
 */

MockActionProtocol mock;
std::function<void(void *, unsigned int)> sendBytes =
        [](void * retuncode, unsigned int size) { mock.sendBytes(retuncode,size); };

ClientProtocol serverProtocol(sendBytes);

TEST_CASE("ClientProtocol serialize ActionCreateRoom","[clientProtocol]"){
    uint8_t capacity = 1 ;
    std::string name = "roomCreate";

    std::shared_ptr<ClientAction> action = std::make_shared<ActionCreateRoom>(capacity,name);

    serverProtocol.serializeAction(action);

    REQUIRE(action->getType() == CREATE );
    REQUIRE(mock.getCapacity() == 1);
    REQUIRE(mock.getSizeName() == name.size());
    REQUIRE(mock.getName( name.size()) == name);
}

TEST_CASE("ClientProtocol serialize ActionJoinRoom","[clientProtocol]"){
    std::string name = "roomJoin";

    std::shared_ptr<ClientAction> action = std::make_shared<ActionJoinRoom>(name);

    serverProtocol.serializeAction(action);

    REQUIRE(action->getType() == JOIN );
    REQUIRE(mock.getSizeName() == name.size());
    REQUIRE(mock.getName( name.size()) == name);
}

TEST_CASE("ClientProtocol serialize ActionListRoom","[clientProtocol]"){
    std::shared_ptr<ClientAction> action = std::make_shared<ActionListRooms>();

    serverProtocol.serializeAction(action);

    REQUIRE(action->getType() == LIST );
}

TEST_CASE("ClientProtocol serialize ActionMove","[clientProtocol]"){
    uint8_t id = 1 ;
    uint8_t direction = 1 ;

    std::shared_ptr<ClientAction> action = std::make_shared<ClientActionMove>(id,direction,true);

    serverProtocol.serializeAction(action);

    REQUIRE(action->getType() == MOVE );
    REQUIRE(mock.getId() == id);
    REQUIRE(mock.getDirection() == direction);
    REQUIRE(mock.getState() == true);
}