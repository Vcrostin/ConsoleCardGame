//
// Created by brostin on 12.03.2022.
//

#pragma once

#include "card.h"
#include "user.h"
#include <vector>
#include <memory>

namespace Core {

    class Board {
    public:
        Board();
    private:
        // User user1;
        // User user2;
        std::vector<std::shared_ptr<Card>> cards;
    };
}
