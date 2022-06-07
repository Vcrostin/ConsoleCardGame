project(config_tests)

enable_testing()
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(ConfigTests ConfParserTest.cpp)
target_link_libraries(ConfigTests HearthtoneConf)
target_link_libraries(ConfigTests gtest gtest_main)
add_test(NAME ConfigTests COMMAND ConfigTests)
