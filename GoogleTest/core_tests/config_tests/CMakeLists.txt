project(config_tests)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/general.cfg
        ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)

enable_testing()
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(ConfigTests ConfParserTest.cpp general.cfg)
target_link_libraries(ConfigTests HearthtoneConf)
target_link_libraries(ConfigTests gtest gtest_main)
add_test(NAME ConfigTests COMMAND ConfigTests)
