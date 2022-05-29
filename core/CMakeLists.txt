project(HearthstoneConsoleLib)

add_subdirectory(card_types)

add_library(HearthstoneConsoleLib
        board.cpp board.h
        user.cpp user.h
        utils/string_assist.cpp
        utils/string_assist.h)
