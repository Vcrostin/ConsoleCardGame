cmake_minimum_required(VERSION 3.21)
project(HearthtoneConsole)

set(CMAKE_CXX_STANDARD 20)

enable_testing()

# add_library(HearthtoneConsole core/card.cpp core/card.h core/board.cpp core/board.h core/user.cpp core/user.h core/utils/string_assist.cpp core/utils/string_assist.h)

add_subdirectory(GoogleTest)
add_subdirectory(core)
