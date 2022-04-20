//
// Created by brostin on 03.04.2022.
//

#pragma once
#include "card.h"
#include "unit_card.h"
namespace Core {
    class BuffCard : public Card{
    public:
        virtual bool Buff(UnitCard) = 0;
    };
}

