//
// Created by brostin on 08.03.2022.
//
#pragma once
#include <string>
#include <array>
#include <vector>

namespace Core {

    class Card {
    public:
        enum class CARD_RARITY {
            UNKNOWN = 0,
            COMMON = 1,
            RARE = 2,
            EPIC = 3,
            LEGENDARY = 4
        };
    protected:
        static const int CARD_WIDTH = 30;
        static const int CARD_HEIGHT = 50;
        bool cardUsable = true;
        Card(int32_t cost, CARD_RARITY cardType);

    public:
        [[nodiscard]]
        constexpr inline int32_t GetCost() const {
            return cost;
        }

        [[nodiscard]]
        constexpr inline CARD_RARITY GetCardType() const {
            return cardType;
        }

        //by the starting coordinates print cards from
        // minicard will be consistant on whole sceen, although when u pick card u see it full screen
        // virtual void print_card() = 0;

        // formatted output this is based
        // protected with args and use??
        // virtual still usefull
        // [[nodiscard]] virtual std::string ShowInfo() const = 0;

    private:
        int32_t cost;
        CARD_RARITY cardType;
    };
}
