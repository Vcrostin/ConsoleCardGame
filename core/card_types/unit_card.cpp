//
// Created by brostin on 03.04.2022.
//

#include "unit_card.h"

Core::UnitCard::UnitCard(int32_t health, int32_t attack, int32_t cost, CARD_TYPE cardType) : maxHealth(health), maxAttack(attack),
                                                                                             Card(cost, cardType) {
    curAttack = attack;
    curHealth = health;
}

void Core::UnitCard::Attack(Core::UnitCard& uc) const {
    uc.curHealth -= curAttack;
}

void Core::UnitCard::AfterTurnActions() {
    if (!AliveCheck())
        DeadAction();
}
