//
// Created by roby on 13/11/22.
//
#include <catch2/catch_test_macros.hpp>
#include "sub_server/Action.h"


TEST_CASE("Action type is set correctly", "[Action]") {
    std::vector<uint8_t> data;
    Action action(CREATE_ROOM, data);
    REQUIRE(action.getType() == CREATE_ROOM);
}

TEST_CASE("Action data is set correctly", "[Action]") {
    std::vector<uint8_t> data(1);
    data.push_back(1);
    Action action(CREATE_ROOM, data);
//    REQUIRE(action.getData().empty());
    REQUIRE(1 == action.getData().back());
}

TEST_CASE("When action type is 1 (create action), data is a string", "[Action]") {
    std::string roomsName = "room's name";
    std::vector<uint8_t> data(roomsName.begin(), roomsName.end());
    Action action(CREATE_ROOM, data);
    std::string answer_string(data.begin(), data.end());
    REQUIRE(roomsName == answer_string);
}

TEST_CASE("When action type is 2 (join action), data is a string", "[Action]") {
    std::string roomsName = "room's name";
    std::vector<uint8_t> data(roomsName.begin(), roomsName.end());
    Action action(JOIN_ROOM, data);
    std::string answer_string(data.begin(), data.end());
    REQUIRE(roomsName == answer_string);
}

TEST_CASE("When action type is 3 (list action), data is empty", "[Action]") {
    std::vector<uint8_t> data;
    Action action(LIST_ROOMS, data);
    REQUIRE(data.empty());
}

TEST_CASE("When action type is 4 (movement action), data is a byte representing the move tbd", "[Action]") {
    std::vector<uint8_t> data(1);
    data.push_back(1);
    Action action(MOVE, data);
    REQUIRE(1 == action.getData().back());
}

TEST_CASE("Action can be created with a string as data", "[Action]") {
    std::string roomsName = "room's name";
    Action action(CREATE_ROOM, roomsName);
    REQUIRE(action.getData().size() == roomsName.size());
    REQUIRE((char) action.getData().back() == roomsName.back());
    REQUIRE((char) action.getData().front() == 'r');
}