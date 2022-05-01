project(cards)

add_subdirectory(cards_gen)

add_library(Cards
        buff_card.cpp buff_card.h
        card.cpp card.h
        damage_card.cpp damage_card.h
        unit_card.cpp unit_card.h
        card_type.cpp card_type.h)
