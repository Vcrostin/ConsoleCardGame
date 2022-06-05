project(core_tests)

enable_testing()
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_subdirectory(util_tests)
add_subdirectory(config_tests)

# add_executable(core_tests split_test.cpp strip_test.cpp multiply_string_test.cpp replace_chars_test.cpp ConfParserTest.cpp)
# target_link_libraries(StringLibsTest HearthtoneConsoleLib)
# target_link_libraries(StringLibsTest gtest gtest_main)
# add_test(NAME StringLibsTest COMMAND StringLibsTest)
