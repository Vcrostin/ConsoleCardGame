//
// Created by brostin on 03.04.2022.
//

#include "buff_card.h"

#include <utility>
#include "card_type.h"

Core::BuffCard::BuffCard(int32_t buffValue, int32_t cost, Core::Card::CARD_RARITY cardType, std::function<bool(UnitCard&)> fc) : buffValue(buffValue), fc(std::move(fc)), Card(cost, cardType){

}

void Core::BuffCard::Buff(Core::UnitCard &unitCard) {
    fc(unitCard);
}

[[maybe_unused]] bool BuffBoolType = Core::CardType::getInstance()->AddType("BuffCard", [](){
});
