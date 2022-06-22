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

        bool AddUser(const User &user);

        bool IsBusy() const;

        bool StartGameBoard();

    private:
        std::unique_ptr<User> firstUser;
        std::unique_ptr<User> secondUser;
        // TODO: move desk to users field like hand and desk cards
        std::vector<std::shared_ptr<Card>> cards;
    };
}
