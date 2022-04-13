﻿//
// Created by brostin on 08.03.2022.
//
#pragma once
#include <string>
#include <array>

namespace Core {

    class Card {
    public:
        enum class CARD_TYPE {
            UNKNOWN = 0,
            COMMON = 1,
            RARE = 2,
            EPIC = 3,
            LEGENDARY = 4
        };
    protected:
        static const int CARD_WIDTH = 30;
        static const int CARD_HEIGHT = 50;
        Card(int32_t cost, CARD_TYPE cardType);

    public:
        [[nodiscard]]
        constexpr inline int32_t GetCost() const {
            return cost;
        }

        [[nodiscard]]
        constexpr inline CARD_TYPE GetCardType() const {
            return cardType;
        }

        [[nodiscard]]
        inline virtual std::array<std::array<int,CARD_WIDTH>, CARD_HEIGHT> ShowCard() const {
            return {{}};
        }

        // formatted output this is based
        // protected with args and use??
        // virtual still usefull
        [[nodiscard]] virtual std::string ShowInfo() const = 0;

    private:
        int32_t cost;
        CARD_TYPE cardType;

    };
}