# These tests can use the Catch2-provided main
add_executable(tests protocoloTest.cpp
        ../libs/sub_common/protocolo.cpp
        ../libs/sub_common/protocolo.h
        serverTest.cpp
        blockingQueueTest.cpp
        ../libs/sub_common/thread.h
        ../libs/sub_common/thread.cpp
        actionsTest.cpp ../libs/sub_common/sub_action/ActionCreate.cpp ../libs/sub_common/sub_action/ActionCreate.h ../libs/sub_common/sub_action/ActionJoin.cpp ../libs/sub_common/sub_action/ActionJoin.h ../libs/sub_common/sub_action/ActionList.cpp ../libs/sub_common/sub_action/ActionList.h)
target_link_libraries(tests PRIVATE Catch2::Catch2WithMain lib_common)