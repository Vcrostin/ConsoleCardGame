project(server)

set(BOOST_ROOT /usr/include/boost)
set(Boost_USE_STATIC_LIBS ON)
set(CMAKE_CXX_STANDARD 20)
find_package(Boost COMPONENTS system thread REQUIRED)

include_directories(${Boost_INCLUDE_DIR})
add_executable(Server
        com_handler.cpp com_handler.h
        main.cpp server.cpp server.h)
target_link_libraries(Server ${Boost_LIBRARIES})
target_link_libraries(Server ConsoleCardLib ConsoleCardConf)
