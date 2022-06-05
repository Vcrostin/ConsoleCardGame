project(util_test)

enable_testing()
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(UtilTest split_test.cpp strip_test.cpp multiply_string_test.cpp replace_chars_test.cpp)
target_link_libraries(UtilTest HearthtoneConsoleLib)
target_link_libraries(UtilTest gtest gtest_main)
add_test(NAME UtilTest COMMAND UtilTest)
