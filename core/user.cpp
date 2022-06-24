//
// Created by brostin on 12.03.2022.
//

#include "user.h"


//Core::User::User(uint64_t sessionId, const std::string_view& userName, int32_t lvl,
//                 Core::User::UserStatus userStatus) :
//                 sessionId(sessionId), userName(userName), level(lvl), userStatus(userStatus) {
//}


Core::User::User(const std::string_view &userName) : sessionId(0), userName(userName) {

}
