project(server)

set(BOOST_ROOT /usr/include/boost)
set(Boost_USE_STATIC_LIBS ON)
find_package(Boost COMPONENTS system thread)

include_directories(${Boost_INCLUDE_DIR})
add_executable(server main.cpp)
target_link_libraries(server ${Boost_LIBRARIES})
