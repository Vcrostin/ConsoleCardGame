project(config_tests)

enable_testing()
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/general.cfg
        ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)

add_executable(ConfigTests ConfParserTest.cpp)
target_link_libraries(ConfigTests ConsoleCardConf ConsoleCardLib)
target_link_libraries(ConfigTests gtest gtest_main)
add_test(NAME ConfigTests COMMAND ConfigTests)
