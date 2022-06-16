//
// Created by brostin on 16.06.22.
//

#pragma once

#include "card.h"
#include "unit_card.h"

namespace Core {
    class RecoveryCard : public Card {
    public:
        RecoveryCard(int32_t heal, int32_t cost, CARD_RARITY cardType);

        virtual void Heal(UnitCard &uc);

    private:
        int32_t heal;
    };

    extern bool RecoveryBoolType;
}


