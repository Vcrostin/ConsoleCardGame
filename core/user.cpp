//
// Created by brostin on 12.03.2022.
//

#include "user.h"


//Core::User::User(uint64_t sessionId, const std::string_view& userName, int32_t lvl,
//                 Core::User::UserStatus userStatus) :
//                 sessionId(sessionId), userName(userName), level(lvl), userStatus(userStatus) {
//}


Core::User::User(const std::string_view &userName) : sessionId(0), userName(userName),
                                                     userStatus(UserStatus::NOT_CONNECTED) {

}

void Core::User::SetSessionId(uint64_t idSession) {
    sessionId = idSession;
}

uint64_t Core::User::GetSessionId() const {
    return sessionId;
}

void Core::User::SetUserStatus(int32_t statusCode) {
    if (statusCode < 0 || statusCode > 2) {
        // TODO: make custom exception class
    }
    userStatus = static_cast<UserStatus>(statusCode);
}
