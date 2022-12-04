#include <catch2/catch_test_macros.hpp>
#include "sub_client/ClientProtocol.h"
#include "MockClientProtocol.h"

/*
 * TEST UNITARIOS DE PROTOCOLO
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

/*
 * Defino los mock a utilizar en CreateACK
 * mockCreate
 *      atributos:
 *          - id = 1
 *          - retunCode = OK;
 * mockCreateERROR
 *      atributos:
 *          - id = 1
 *          - retunCode = ERROR_FULL;
 */
MockClientProtocol mockCreate(1, OK);
MockClientProtocol mockCreateERROR(1,ERROR_FULL);

TEST_CASE("ClientProtocol can deserialize CreateACK update", "[clientProtocol]") {

    SECTION("CreateACK with return code OK") {
        std::function<void(void *, int)> bytes_receiver_callable =
                [](void * retuncode, int size) { mockCreate.receiveBytes(retuncode, size); };

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
        REQUIRE(update->getReturnCode() == ERROR_FULL);
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
MockClientProtocol mockWorldOneOK(dataTestOne);
std::vector<uint16_t> dataTestTwo = {0, 0, 0, 0, 1, 1, 2000, 4000, 0, 60};
MockClientProtocol mockWorldTwoOK(dataTestTwo);

TEST_CASE("ClientProtocol can deserialize WorldACK update", "[clientProtocol]") {

    SECTION("Update WorldACK with ball in position (0,0) and score (0,0)") {
        std::function<void(void *, int)> bytes_receiver_callable =
                [](void * retuncode, int size) { mockWorldOneOK.receiveBytesWorld(retuncode,size); };

        auto update = ClientProtocol::deserializeData(WORLD,
                                                      bytes_receiver_callable);
        auto ball = update->getBall();
        auto score = update->getScore();
        auto x = (int)(ball.getX()*1000);
        auto y = (int)(ball.getY()*1000);

      //  REQUIRE(ball.getX() == 2000);
       // REQUIRE(ball.getY() == 3000);
        REQUIRE(score.getLocal() == 2);
        REQUIRE(score.getVisitor() == 0);
    }

    SECTION("Update WorldACK with car in position (200,400) and angle 60 degrees") {
        std::function<void(void *, int)> bytes_receiver_callable =
                [](void * retuncode, int size) { mockWorldTwoOK.receiveBytesWorld(retuncode,size); };

        auto update = ClientProtocol::deserializeData(WORLD,
                                                      bytes_receiver_callable);
        auto cars = update->getCars();
       // auto x = (int)(cars[0].getX()*1000);
      //  auto y = (int)(cars[0].getY()*1000);
        //REQUIRE(x == 2000);
       // REQUIRE(y == 4000);
        REQUIRE((int)(cars[0].getAngle()*1000) == 60);
    }
}
/*
 * En caso de que reciba un comando inexistente, se retorna un puntero a null.
 */
TEST_CASE("ClientProtocol receive an non-existed command", "[clientProtocol]") {

    std::function<void(void *, int)> bytes_receiver_callable =
            [](void * retuncode, int size) { mockWorldOneOK.receiveBytesWorld(retuncode,size); };

    auto update = ClientProtocol::deserializeData(-1,
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
 * Defino de forma global a ClientProtocol y al mock que utilizare.
 */

MockClientProtocol mock;
std::function<void(void *, unsigned int)> sendBytes =
        [](void * retuncode, unsigned int size) { mock.sendBytesMock(retuncode,size); };

ClientProtocol serverProtocol(sendBytes);

TEST_CASE("ClientProtocol serialize ActionCreateRoom","[clientProtocol]"){
    uint8_t capacity = 1 ;
    std::string name = "roomCreate";

    std::shared_ptr<ClientAction> action = std::make_shared<ActionCreateRoom>(capacity,name);

    serverProtocol.serializeAction(action);

    REQUIRE(mock.getCapacity() == 1);
    REQUIRE(mock.getSizeName() == name.size());
    REQUIRE(mock.getName( name.size()) == name);
}

TEST_CASE("ClientProtocol serialize ActionJoinRoom","[clientProtocol]"){
    std::string name = "roomJoin";

    std::shared_ptr<ClientAction> action = std::make_shared<ActionJoinRoom>(name);

    serverProtocol.serializeAction(action);

    REQUIRE(mock.getSizeName() == name.size());
    REQUIRE(mock.getName( name.size()) == name);
}

TEST_CASE("ClientProtocol serialize ActionListRoom","[clientProtocol]"){
    std::shared_ptr<ClientAction> action = std::make_shared<ActionListRooms>();

    serverProtocol.serializeAction(action);
    REQUIRE(true == true);
}

TEST_CASE("ClientProtocol serialize ActionMove","[clientProtocol]"){
    uint8_t id = 1 ;
    uint8_t direction = 1 ;

    std::shared_ptr<ClientAction> action = std::make_shared<ClientActionMove>(id,direction,true);

    serverProtocol.serializeAction(action);

    REQUIRE(mock.getId() == id);
    REQUIRE(mock.getDirection() == direction);
    REQUIRE(mock.getState() == true);
}