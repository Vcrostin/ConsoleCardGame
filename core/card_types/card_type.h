//
// Created by brostin on 28.04.22.
//

#pragma once

#include <memory>
#include <string>
#include <vector>
#include <functional>
#include <unordered_map>
#include <string_view>

namespace Core {
    class CardType {

    protected:
        using ContainParm = std::unordered_map<std::string, std::function<void()>>;
        ContainParm vct;
    public:
        static std::shared_ptr<CardType> getInstance();

        /// string: card type, function: action
        bool AddType(const std::string &, const std::function<void()> &);

#pragma region iterators

        decltype(auto) begin() {
            return vct.begin();
        }

        decltype(auto) end() {
            return vct.end();
        }

        decltype(auto) begin() const {
            return vct.begin();
        }

        decltype(auto) end() const {
            return vct.end();
        }

#pragma endregion

#pragma region operators

        std::function<void()> &operator[](const std::string &str);

        std::function<void()> operator[](const std::string &str) const = delete;

#pragma endregion


    private:
        static inline std::shared_ptr<CardType> CurInstance;

        CardType() = default;

    };
}

