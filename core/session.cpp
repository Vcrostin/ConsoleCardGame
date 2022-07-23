//
// Created by brostin on 23.07.22.
//

#include "session.h"

bool Core::Session::AddUser(const Core::User &user) {
    if (firstUser == nullptr) {
        firstUser = std::make_unique<User>(user);
        return true;
    }
    if (secondUser == nullptr) {
        secondUser = std::make_unique<User>(user);
        return true;
    }
    return false;
}

bool Core::Session::IsBusy() const {
    return !(firstUser == nullptr || secondUser == nullptr);
}
