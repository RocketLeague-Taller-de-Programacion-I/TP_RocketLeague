# These tests can use the Catch2-provided main
add_executable(tests protocoloTest.cpp
        ../libs/sub_common/protocolo.cpp
        ../libs/sub_common/protocolo.h
        serverTest.cpp
        blockingQueueTest.cpp
        ../libs/sub_common/thread.h
        ../libs/sub_common/thread.cpp
        actionsTest.cpp ../libs/sub_common/ActionCreate.cpp ../libs/sub_common/ActionCreate.h ../libs/sub_common/ActionJoin.cpp ../libs/sub_common/ActionJoin.h ../libs/sub_common/ActionList.cpp ../libs/sub_common/ActionList.h)
target_link_libraries(tests PRIVATE Catch2::Catch2WithMain lib_common)