//
// Created by brostin on 08.03.2022.
//

#include "card.h"

namespace Core {
    Card::Card(int32_t cost, CARD_TYPE cardType) : cost(cost), cardType(cardType) {
        if (cardType == CARD_TYPE::UNKNOWN)
            throw std::invalid_argument("Expected actual type, got default type");
    }

}
