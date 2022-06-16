//
// Created by brostin on 03.04.2022.
//

#pragma once

#include "card.h"
#include "unit_card.h"
#include <functional>

namespace Core {
    class [[deprecated]] BuffCard : public Card {
    public:
        BuffCard(int32_t buffValue, int32_t cost, CARD_RARITY cardType, std::function<bool(UnitCard &)> fc);

        void Buff(UnitCard &);

    private:
        int32_t buffValue;
        std::function<bool(UnitCard &)> fc;
    };

    extern bool BuffBoolType;
}

