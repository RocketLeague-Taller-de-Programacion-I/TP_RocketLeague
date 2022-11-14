# These tests can use the Catch2-provided main
add_executable(tests actionsTest.cpp)
target_link_libraries(tests PRIVATE Catch2::Catch2WithMain lib_common)