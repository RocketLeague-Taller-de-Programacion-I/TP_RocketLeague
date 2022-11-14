find_package(Catch2 3 REQUIRED)

add_executable(tests
        protocoloTest.cpp
        ../libs/sub_common/protocolo.cpp
        ../libs/sub_common/protocolo.h
        serverTest.cpp blockingQueueTest.cpp ../libs/sub_common/thread.h ../libs/sub_common/thread.cpp)

target_link_libraries(tests PRIVATE Catch2::Catch2WithMain)