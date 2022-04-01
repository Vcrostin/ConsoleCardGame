project(Google_Tests)

add_subdirectory(lib)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(Google_Tests split_test.cpp)
target_link_libraries(Google_Tests HearthtoneConsole)
target_link_libraries(Google_Tests gtest gtest_main)