//
// Created by brostin on 03.04.2022.
//

#include "card_type.h"
#include "unit_card.h"

Core::UnitCard::UnitCard(int32_t health, int32_t attack, int32_t cost, CARD_RARITY cardType) : maxHealth(health),
                                                                                               maxAttack(attack),
                                                                                               Card(cost, cardType) {
    curAttack = attack;
    curHealth = health;
}

void Core::UnitCard::TakeDamage(int32_t damage) {
    curHealth -= damage;
}

void Core::UnitCard::AfterTurnActions() {
    if (!AliveCheck())
        DeadAction();
}

[[maybe_unused]] bool UnitBoolType = Core::CardType::getInstance()->AddType("UnitCard", []() {
});
