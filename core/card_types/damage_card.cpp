//
// Created by brostin on 03.04.2022.
//

#include "card_type.h"
#include "damage_card.h"

Core::DamageCard::DamageCard(int32_t damage, int32_t cost, Core::Card::CARD_RARITY cardType) : damage(damage), Core::Card(cost, cardType){

}

void Core::DamageCard::Damage(Core::UnitCard &uc) {
    uc.TakeDamage(damage);
}

[[maybe_unused]] bool DamageBoolType = Core::CardType::getInstance()->AddType("DamageCard", [](){
});
