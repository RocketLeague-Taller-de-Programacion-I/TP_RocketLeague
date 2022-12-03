# These tests can use the Catch2-provided main
add_executable(testsClient
        ClientProtocolTest.cpp
        MockClientProtocol.h)
add_executable(testsServer
        ServerProtocolTest.cpp
        MockServerProtocol.h)

# These tests can use the Catch2-provided main
find_package(Catch2 3 REQUIRED)
target_link_libraries(testsClient PRIVATE Catch2::Catch2WithMain lib_client )
target_link_libraries(testsServer PRIVATE Catch2::Catch2WithMain lib_server box2d)