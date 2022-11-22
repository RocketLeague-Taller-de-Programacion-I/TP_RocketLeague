# These tests can use the Catch2-provided main
add_executable(tests protocoloTest.cpp
        ../libs/sub_common/protocolo.cpp
        ../libs/sub_common/protocolo.h
        serverTest.cpp
        blockingQueueTest.cpp
        ../libs/sub_common/thread.h
        ../libs/sub_common/thread.cpp
        actionsTest.cpp ../libs/sub_server/ActionCreateServer.cpp ../libs/sub_server/ActionCreateServer.h ../libs/sub_server/ActionJoinServer.cpp ../libs/sub_server/ActionJoinServer.h ../libs/sub_server/ActionListServer.cpp ../libs/sub_server/ActionListServer.h)
target_link_libraries(tests PRIVATE Catch2::Catch2WithMain lib_common)