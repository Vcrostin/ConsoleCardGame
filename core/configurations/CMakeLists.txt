project(HearthtoneConf)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/general.cfg
        ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
# TODO: make add files easier
add_library(HearthtoneConf conf_parser.cpp conf_parser.h general.cfg)

target_link_libraries(HearthtoneConf HearthtoneConsoleLib)
