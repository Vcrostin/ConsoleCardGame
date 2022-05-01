project(client)

set(BOOST_ROOT /usr/include/boost)
set(Boost_USE_STATIC_LIBS ON)
find_package(Boost COMPONENTS system thread)

include_directories(${Boost_INCLUDE_DIR})
add_executable(client main.cpp)
target_link_libraries(client ${Boost_LIBRARIES})
