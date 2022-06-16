//
// Created by brostin on 16.06.22.
//

#include "card_type.h"
#include "recovery_card.h"

Core::RecoveryCard::RecoveryCard(int32_t heal, int32_t cost, Core::Card::CARD_RARITY cardType) :
        heal(heal),
        Core::Card(cost,
                   cardType) {

}

void Core::RecoveryCard::Heal(Core::UnitCard &uc) {
    uc.TakeDamage(-heal);
}

[[maybe_unused]] bool RecoveryBoolType = Core::CardType::getInstance()->AddType("RecoveryCard", []() {
});
