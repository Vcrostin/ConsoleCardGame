//
// Created by brostin on 03.04.2022.
//

#include "gtest/gtest.h"
#include "../../core/card_types/buff_card.h"
#include "../../core/card_types/damage_card.h"
#include "../../core/card_types/unit_card.h"
#include <vector>

std::vector<Core::Card::CARD_TYPE> cardTypes = {
        Core::Card::CARD_TYPE::COMMON,
        Core::Card::CARD_TYPE::RARE,
        Core::Card::CARD_TYPE::EPIC,
        Core::Card::CARD_TYPE::LEGENDARY,
};

TEST(cards_test, init) {
    EXPECT_ANY_THROW(Core::BuffCard buffCard(0, 0, Core::Card::CARD_TYPE::UNKNOWN, [](Core::UnitCard&){return true;}));
    EXPECT_ANY_THROW(Core::DamageCard damageCard(0, 0, Core::Card::CARD_TYPE::UNKNOWN));
    EXPECT_ANY_THROW(Core::UnitCard unitCard(0, 0, 0 ,Core::Card::CARD_TYPE::UNKNOWN));
    for (const auto& cardType : cardTypes) {
        EXPECT_NO_THROW(Core::BuffCard buffCard(0, 0, cardType, [](Core::UnitCard&){return true;}));
        EXPECT_NO_THROW(Core::DamageCard damageCard(0, 0, cardType));
        EXPECT_NO_THROW(Core::UnitCard unitCard(0, 0, 0 ,cardType));
    }
}
