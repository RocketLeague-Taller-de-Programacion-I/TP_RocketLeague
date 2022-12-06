# These tests can use the Catch2-provided main
add_executable(testsClient
        client_protocol_test/ClientProtocolTest.cpp
        client_protocol_test/MockACKProtocol.h
        client_protocol_test/MockWorldProtocol.h
        client_protocol_test/MockActionProtocol.h)
add_executable(testCommon blockingQueueTest.cpp)
add_executable(testsServer
        server_protocol_test/ServerProtocolTest.cpp
        server_protocol_test/MockMoveProtocol.h
        server_protocol_test/MockActionProtocol.h
        server_protocol_test/MockUpdateProtocol.h
        server_protocol_test/MockUpdateWorldProtocol.h
        server_protocol_test/MockStatsProtocol.h
        GamesTest.cpp)

# These tests can use the Catch2-provided main
find_package(Catch2 3 REQUIRED)
target_link_libraries(testCommon Catch2::Catch2WithMain lib_common)
target_link_libraries(testsClient PRIVATE Catch2::Catch2WithMain lib_client )
target_link_libraries(testsServer PRIVATE Catch2::Catch2WithMain lib_server box2d)
