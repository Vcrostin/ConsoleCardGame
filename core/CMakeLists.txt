project(HearthtoneConsoleLib)

add_subdirectory(card_types)
add_subdirectory(configurations)

add_library(HearthtoneConsoleLib
        board.cpp board.h
        user.cpp user.h
        utils/string_assist.cpp
        utils/string_assist.h utils/path_manip.cpp utils/path_manip.h)
