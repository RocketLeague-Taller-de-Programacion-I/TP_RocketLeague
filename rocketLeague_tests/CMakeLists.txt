# 'Google_test' is the subproject name
project(rocketLeague_tests)

# 'lib' is the folder with Google Test sources
add_subdirectory(lib)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

# 'Google_Tests_run' is the target name
# 'test1.cpp tests2.cpp' are source files with tests
# add_executable(Google_Tests_run test1.cpp tests2.cpp)
# target_link_libraries(Google_Tests_run gtest gtest_main)
# adding the Google_Tests_run target
add_executable(protocolo_test_run protocoloTest.cpp)

# linking Google_Tests_run with DateConverter_lib which will be tested
target_link_libraries(protocolo_test_run sub_client)

target_link_libraries(protocolo_test_run gtest gtest_main)