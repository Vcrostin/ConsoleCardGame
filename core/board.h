//
// Created by brostin on 12.03.2022.
//

#pragma once

#include "card_types/card.h"
#include "user.h"
#include <vector>
#include <memory>

namespace Core {

    class Board {
    public:
        Board();
    private:
        std::unique_ptr<User> cur_user;
        std::unique_ptr<User> opponent_user;
        std::vector<std::shared_ptr<Card>> cards;
    };
}
