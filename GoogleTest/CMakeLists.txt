project(basic_test)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(lib)
enable_testing()
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_subdirectory(core_tests)
add_subdirectory(client_tests)

