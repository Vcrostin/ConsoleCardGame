project(basic_test)

add_subdirectory(lib)
enable_testing()
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})



add_executable(StringLibsTest split_test.cpp strip_test.cpp multiply_string_test.cpp replace_chars_test.cpp)
target_link_libraries(StringLibsTest HearthtoneConsoleLib)
target_link_libraries(StringLibsTest gtest gtest_main)
add_test(NAME StringLibsTest COMMAND StringLibsTest)
