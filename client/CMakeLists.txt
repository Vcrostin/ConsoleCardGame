project(client)

set(BOOST_ROOT /usr/include/boost)
set(Boost_USE_STATIC_LIBS ON)
set(CMAKE_CXX_STANDARD 20)
find_package(Boost COMPONENTS system thread REQUIRED)

include_directories(${Boost_INCLUDE_DIR})
add_executable(client main.cpp client_sender.cpp client_sender.h)
target_link_libraries(client ${Boost_LIBRARIES})
target_link_libraries(client HearthtoneConsoleLib Cards)
