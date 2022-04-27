project(client_tests)

enable_testing()
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(ClientTests card_test.cpp)
target_link_libraries(ClientTests HearthtoneConsoleLib Cards)
target_link_libraries(ClientTests gtest gtest_main)
add_test(NAME ClientTests COMMAND ClientTests)
