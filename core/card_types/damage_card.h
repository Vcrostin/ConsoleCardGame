//
// Created by brostin on 03.04.2022.
//

#pragma once

#include "card.h"
#include "unit_card.h"

namespace Core {
    class DamageCard : public Core::Card {
    public:
        DamageCard(int32_t damage, int32_t cost, CARD_RARITY cardType);

        virtual void Damage(UnitCard &uc);

    private:
        int32_t damage;
    };

    extern bool DamageBoolType;
}

