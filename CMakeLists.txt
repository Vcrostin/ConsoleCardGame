cmake_minimum_required(VERSION 3.21)
project(ConsoleCardGame)

set(CMAKE_CXX_STANDARD 20)

enable_testing()

add_subdirectory(GoogleTest)
add_subdirectory(core)
add_subdirectory(server)
add_subdirectory(client)
