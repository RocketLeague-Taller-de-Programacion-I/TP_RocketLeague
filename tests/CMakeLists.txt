
find_package(Catch2 3 REQUIRED)

add_executable(tests protocoloTest.cpp ../sub_common/protocolo.cpp ../sub_common/protocolo.h)

target_link_libraries(tests PRIVATE Catch2::Catch2WithMain)