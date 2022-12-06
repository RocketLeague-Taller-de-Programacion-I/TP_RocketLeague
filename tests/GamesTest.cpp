#include <catch2/catch_test_macros.hpp>
#include "sub_server/gameManager.h"



TEST_CASE("Create a game", "[serverProtocol]"){

    std::function<void(ProtectedQueue<std::shared_ptr<ServerAction>> *,
            BlockingQueue<std::optional<std::shared_ptr<ServerUpdate>>> *)> startThreadsCallable =
            [](ProtectedQueue<std::shared_ptr<ServerAction>> * qP,
                    BlockingQueue<std::optional<std::shared_ptr<ServerUpdate>>> * qB) { };

    GameManager gameManager;
    uint8_t id = 1;
    uint8_t capacity = 2;
    std::string name = "testCreateGame";


    SECTION("Game is success created"){
        REQUIRE(gameManager.createGame(id,capacity,name,startThreadsCallable));
        gameManager.cleanGames();
    }
    SECTION("Game is error created why the game is allready existed"){
        REQUIRE(gameManager.createGame(id,capacity,name,startThreadsCallable));
        /*
         * The game is already created
         */
        REQUIRE_FALSE(gameManager.createGame(id,capacity,name,startThreadsCallable));
        gameManager.cleanGames();
    }
}

TEST_CASE("Join a game", "[serverProtocol]"){

    std::function<void(ProtectedQueue<std::shared_ptr<ServerAction>> *,
                       BlockingQueue<std::optional<std::shared_ptr<ServerUpdate>>> *)> startThreadsCallable =
            [](ProtectedQueue<std::shared_ptr<ServerAction>> * qP,
               BlockingQueue<std::optional<std::shared_ptr<ServerUpdate>>> * qB) { };

    GameManager gameManager;
    uint8_t id = 1;
    uint8_t capacity = 2;
    std::string name = "testJoinGame";

    REQUIRE(gameManager.createGame(id,capacity,name,startThreadsCallable));

    SECTION("Game is success join"){
        uint8_t id2 = 2;
        REQUIRE(gameManager.joinGame(id2,name,startThreadsCallable));
        gameManager.deletePlayer(id2);
    }
    SECTION("Game is error join why the game is full"){
        uint8_t id2 = 2;
        uint8_t id3 = 3;
        REQUIRE(gameManager.joinGame(id2,name,startThreadsCallable));
        REQUIRE_FALSE(gameManager.joinGame(id3,name,startThreadsCallable));
        gameManager.deletePlayer(id2);
    }
}
TEST_CASE("List a game", "[serverProtocol]"){

    std::function<void(ProtectedQueue<std::shared_ptr<ServerAction>> *,
                       BlockingQueue<std::optional<std::shared_ptr<ServerUpdate>>> *)> startThreadsCallable =
            [](ProtectedQueue<std::shared_ptr<ServerAction>> * qP,
               BlockingQueue<std::optional<std::shared_ptr<ServerUpdate>>> * qB) { };

    GameManager gameManager;
    uint8_t id = 1;
    uint8_t capacity = 2;
    std::string name = "testListGame";

    SECTION("GameManager contain zero games]"){
        std::vector<uint8_t> listGames;
        /*
        * return cant of games in gameManager
        */
        REQUIRE(gameManager.listGames(id,listGames) == 0);
    }
    SECTION("Create the game and success list"){
        REQUIRE(gameManager.createGame(id,capacity,name,startThreadsCallable));

        std::vector<uint8_t> listGames;
        /*
        * return cant of games in gameManager
        */
        REQUIRE(gameManager.listGames(id,listGames) == 1);
        std::string nameReceiver(listGames.begin()+3,listGames.end());
        REQUIRE(nameReceiver == name);
    }
}
