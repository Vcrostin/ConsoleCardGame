//
// Created by brostin on 03.04.2022.
//

#include "gtest/gtest.h"
#include "../../core/card_types/buff_card.h"
#include "../../core/card_types/card_type.h"
#include "../../core/card_types/damage_card.h"
#include "../../core/card_types/unit_card.h"
#include <vector>

namespace {
    std::vector<Core::Card::CARD_RARITY> cardTypes = {
            Core::Card::CARD_RARITY::COMMON,
            Core::Card::CARD_RARITY::RARE,
            Core::Card::CARD_RARITY::EPIC,
            Core::Card::CARD_RARITY::LEGENDARY,
    };
}

TEST(cards_test, throw_init) {
    EXPECT_ANY_THROW(Core::BuffCard buffCard(0, 0, Core::Card::CARD_RARITY::UNKNOWN, [](Core::UnitCard&){return true;}));
    EXPECT_ANY_THROW(Core::DamageCard damageCard(0, 0, Core::Card::CARD_RARITY::UNKNOWN));
    EXPECT_ANY_THROW(Core::UnitCard unitCard(0, 0, 0 ,Core::Card::CARD_RARITY::UNKNOWN));
    for (const auto& cardType : ::cardTypes) {
        EXPECT_NO_THROW(Core::BuffCard buffCard(0, 0, cardType, [](Core::UnitCard&){return true;}));
        EXPECT_NO_THROW(Core::DamageCard damageCard(0, 0, cardType));
        EXPECT_NO_THROW(Core::UnitCard unitCard(0, 0, 0 ,cardType));
    }
}

TEST(cards_test, types_test) {
    EXPECT_NO_THROW(Core::CardType::getInstance()->operator[]("BuffCard")());
    EXPECT_NO_THROW(Core::CardType::getInstance()->operator[]("DamageCard")());
    EXPECT_NO_THROW(Core::CardType::getInstance()->operator[]("UnitCard")());
}
