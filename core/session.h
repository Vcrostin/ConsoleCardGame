//
// Created by brostin on 23.07.22.
//

#pragma once

#include "board.h"
#include "user.h"

namespace Core {
    class Session {
    public:
        bool AddUser(const User &user);

        bool IsBusy() const;

    private:
        std::unique_ptr<User> firstUser;
        std::unique_ptr<User> secondUser;
        std::unique_ptr<Board> board;

    };
}

