//
// Created by brostin on 08.03.2022.
//
#pragma once
#include <string>

namespace Core {
    enum class CARD_TYPE {
        UNKNOWN = 0,
        COMMON = 1,
        RARE = 2,
        EPIC = 3,
        LEGENDARY = 4
    };

    class Card {
    public:
        [[nodiscard]]
        constexpr inline int32_t GetCost() const {
            return cost;
        }

        [[nodiscard]]
        constexpr inline CARD_TYPE GetCardType() const {
            return cardType;
        }

        [[nodiscard]] virtual std::string ShowInfo() const = 0;

    protected:

        Card(int32_t cost, CARD_TYPE cardType);

    private:
        int32_t cost;
        CARD_TYPE cardType;

    };
}
