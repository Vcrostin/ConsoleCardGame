//
// Created by brostin on 03.04.2022.
//

#include "damage_card.h"

Core::DamageCard::DamageCard(int32_t damage, int32_t cost, Core::Card::CARD_TYPE cardType) : damage(damage), Core::Card(cost, cardType){

}

void Core::DamageCard::Damage(Core::UnitCard &uc) {
    uc.GetDamage(damage);
}
