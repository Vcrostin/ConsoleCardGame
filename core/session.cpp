//
// Created by brostin on 23.07.22.
//

#include "session.h"

int32_t Core::Session::AddUser(const Core::User &user) {
    if (firstUser == nullptr) {
        firstUser = std::make_unique<User>(user);
        return 1;
    }
    if (secondUser == nullptr) {
        secondUser = std::make_unique<User>(user);
        return 2;
    }
    return 0;
}

bool Core::Session::IsBusy() const {
    return !(firstUser == nullptr || secondUser == nullptr);
}
