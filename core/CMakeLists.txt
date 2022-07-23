project(console_card_lib)

add_subdirectory(card_types)
add_subdirectory(configurations)

add_library(ConsoleCardLib
        board.cpp board.h
        user.cpp user.h
        utils/string_assist.cpp
        utils/string_assist.h utils/path_manip.cpp utils/path_manip.h utils/colours_define.h utils/json.hpp utils/custom_deque.cpp utils/custom_deque.h)

target_link_libraries(ConsoleCardLib Cards)
