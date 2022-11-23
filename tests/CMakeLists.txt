# These tests can use the Catch2-provided main
add_executable(tests protocoloTest.cpp
        ../libs/sub_server/protocolo.cpp
        ../libs/sub_server/protocolo.h
        serverTest.cpp
        blockingQueueTest.cpp
        ../libs/sub_common/thread.h
        ../libs/sub_common/thread.cpp
        actionsTest.cpp ../libs/sub_server/ActionCreate.cpp ../libs/sub_server/ActionCreate.h ../libs/sub_server/ActionJoin.cpp ../libs/sub_server/ActionJoin.h ../libs/sub_server/ActionList.cpp ../libs/sub_server/ActionList.h)
target_link_libraries(tests PRIVATE Catch2::Catch2WithMain lib_common)