//
// Created by brostin on 28.04.22.
//

#include "card_type.h"


std::shared_ptr<Core::CardType> Core::CardType::getInstance() {
    if (CardType::CurInstance == nullptr) {
        CardType::CurInstance = std::shared_ptr<CardType>(new CardType());
    }
    return CardType::CurInstance;
}

bool Core::CardType::AddType(const std::string &str, const std::function<void()> &fc) {
    if (vct.contains(str)) {
        return false;
    }
    vct[str] = fc;
    return true;
}

std::function<void()> &Core::CardType::operator[](const std::string &str) {
    if (vct.count(str) > 0) {
        return vct[str];
    }
    throw std::invalid_argument("This type does not exit in dictionary");
}
