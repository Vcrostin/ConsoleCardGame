//
// Created by brostin on 12.03.2022.
//

#pragma once

#include <string>
#include <string_view>
#include <unordered_map>
#include "card_types/generated_cards/all_generated_classes.h"
#include "utils/json.hpp"

namespace Core {
    class User {
    protected:
    public:
        enum class UserStatus {
            NOT_CONNECTED = 0,
            CONNECTED_FIRST = 1,
            CONNECTED_SECOND = 2,
        };
    private:
        // std::string login;
        uint64_t sessionId;
        std::string userName;
        // TODO: make array_type vector
        std::array<std::shared_ptr<UnitCard>, 2> deskCards;
        std::array<std::shared_ptr<Card>, 5> handCards;
        // int32_t level;
        UserStatus userStatus;
    public:
//        User(uint64_t sessionId, const std::string_view& userName, int32_t lvl,
//             UserStatus userStatus = Core::User::UserStatus::USER);
        nlohmann::json &ToJson(nlohmann::json &json) const {
            json["userName"] = userName;
            json["sessionId"] = sessionId;
            json["status"] = static_cast<int32_t>(userStatus);
            return json;
        }

        explicit User(const std::string_view &userName);

        explicit User(const nlohmann::json &json) {
            userName = json["userName"].get<std::string>();
            sessionId = json["sessionId"].get<uint64_t>();
            userStatus = static_cast<UserStatus>(json["status"].get<int32_t>());
        }

        void SetSessionId(uint64_t sessionId);

        void SetUserStatus(int32_t userStatus);

        [[nodiscard]] uint64_t GetSessionId() const;
    };
}
