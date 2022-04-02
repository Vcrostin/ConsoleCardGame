project(basic_test)

add_subdirectory(lib)
enable_testing()
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})



add_executable(SplitTest split_test.cpp)
target_link_libraries(SplitTest HearthtoneConsoleLib)
target_link_libraries(SplitTest gtest gtest_main)
add_test(NAME SplitTest
        COMMAND SplitTest)

add_executable(StripTest strip_test.cpp)
target_link_libraries(StripTest HearthtoneConsoleLib)
target_link_libraries(StripTest gtest gtest_main)
add_test(NAME StripTest
        COMMAND StripTest)
