//
// Created by brostin on 12.03.2022.
//

#pragma once

#include <string>
#include <string_view>
#include <unordered_map>
#include "card_types/generated_cards/all_generated_classes.h"

namespace Core {
    class User {
    protected:
    public:
        enum class UserStatus {
            USER = 0,
            MODERATOR = 1,
            ADMIN = 2
        };
    private:
        // std::string login;
        // uint64_t sessionId;
        std::string userName;
        std::array<std::shared_ptr<UnitCard>, 2> deskCards;
        std::array<std::shared_ptr<Card>, 5> handCards;
        // int32_t level;
        // UserStatus userStatus;
    public:
//        User(uint64_t sessionId, const std::string_view& userName, int32_t lvl,
//             UserStatus userStatus = Core::User::UserStatus::USER);
        explicit User(const std::string_view &userName);
    };
}
