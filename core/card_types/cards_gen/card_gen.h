//
// Created by brostin on 27.04.22.
//

#pragma once
#include <unordered_map>
#include "../card.h"
#include <string>

namespace Core::Gen {
    class CardGen {
    public:
        constexpr CardGen(const std::string&, std::unordered_map<std::string, std::string>&);
    };
}
