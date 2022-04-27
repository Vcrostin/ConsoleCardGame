//
// Created by brostin on 03.04.2022.
//

#pragma once
#include "card.h"
#include "unit_card.h"
#include <functional>
namespace Core {
    class BuffCard : public Card{
    public:
        BuffCard(int32_t buffValue, int32_t cost, CARD_TYPE cardType, std::function<bool(UnitCard&)> fc);

    private:
        int32_t buffValue;
        std::function<bool(UnitCard&)> fc;
    };
}

