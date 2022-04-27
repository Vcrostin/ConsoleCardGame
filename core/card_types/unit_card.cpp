//
// Created by brostin on 03.04.2022.
//

#include "unit_card.h"

Core::UnitCard::UnitCard(int32_t health, int32_t attack, int32_t cost, CARD_TYPE cardType) : maxHealth(health), maxAttack(attack),
                                                                                             Card(cost, cardType) {
    curAttack = attack;
    curHealth = health;
}

void Core::UnitCard::GetDamage(int32_t damage) {
    curHealth -= damage;
}

void Core::UnitCard::AfterTurnActions() {
    if (!AliveCheck())
        DeadAction();
}
