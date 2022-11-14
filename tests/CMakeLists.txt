# These tests can use the Catch2-provided main

add_executable(tests
        protocoloTest.cpp
        ../libs/sub_common/protocolo.cpp
        ../libs/sub_common/protocolo.h
        serverTest.cpp
        actionsTest.cpp)

target_link_libraries(tests PRIVATE Catch2::Catch2WithMain lib_common)