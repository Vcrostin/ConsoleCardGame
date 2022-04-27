//
// Created by brostin on 03.04.2022.
//

#include "buff_card.h"

#include <utility>

Core::BuffCard::BuffCard(int32_t buffValue, int32_t cost, Core::Card::CARD_TYPE cardType, std::function<bool(UnitCard&)> fc) : buffValue(buffValue), fc(std::move(fc)), Card(cost, cardType){

}
