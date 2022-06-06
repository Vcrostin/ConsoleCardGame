//
// Created by brostin on 03.04.2022.
//

#pragma once

#include "card.h"


namespace Core {
    class UnitCard : public Card {
    public:
        UnitCard(int32_t health, int32_t attack, int32_t cost, CARD_RARITY cardType);

        void TakeDamage(int32_t);

        inline void DeadAction() {
            cardUsable = false;
        }

        [[nodiscard]] inline bool AliveCheck() const {
            return curHealth > 0;
        }

        void AfterTurnActions();

    protected:
        const int32_t maxHealth;
        const int32_t maxAttack;
        int32_t curHealth;
        int32_t curAttack;
    };

    extern bool UnitBoolType;
}


