//
// Created by brostin on 12.03.2022.
//

#pragma once
#include <string>
#include <string_view>

namespace Core {
    class User {
    protected:
    private:
        enum class UserStatus{
            USER = 0,
            MODERATOR = 1,
            ADMIN = 2
        };
        uint64_t userId;
        uint64_t sessionId;
        std::string userName;
        int32_t level;
        UserStatus userStatus;
    public:
        User(uint64_t userId, uint64_t sessionId, const std::string_view& userName, int32_t lvl, UserStatus userStatus);
    };
}
