//
// Created by brostin on 08.03.2022.
//

#include "card.h"

namespace Core {
    Card::Card(int32_t cost, CARD_TYPE cardType) : cost(cost), cardType(cardType) {
    }

    constexpr int32_t Card::GetCost() const {
        return cost;
    }

    constexpr CARD_TYPE Card::GetCardType() const {
        return cardType;
    }
}
