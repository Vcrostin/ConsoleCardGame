//
// Created by brostin on 02.07.22.
//

#pragma once

#include <deque>

template<class T>
class CustomDeque {
private:
    const size_t MAX_LENGTH = 1000;
    std::deque<T> dq;
    std::size_t shift = -1;

public:
    CustomDeque() = default;

    constexpr T &operator[](std::size_t idx) {
        return dq[idx - shift];
    }

    constexpr const T &operator[](std::size_t idx) const {
        return dq[idx - shift];
    }

    [[nodiscard]] constexpr std::size_t Size() const {
        return dq.size();
    }

    [[nodiscard]] constexpr bool IsFull() const {
        return Size() == MAX_LENGTH;
    }

    constexpr bool Push(T &elem) {
        if (IsFull())
            return false;
        dq.push_back(elem);
        return true;
    }

    [[nodiscard]] constexpr bool Empty() const {
        return dq.empty();
    }

    constexpr bool Remove() {
        if (!Empty()) {
            dq.pop_front();
            shift -= 1;
            return true;
        }
        return false;
    }

    [[nodiscard]] constexpr bool InRange(size_t idx) const {
        return 0 - shift <= idx && idx < dq.size() - shift;
    }

    constexpr T &Back() {
        return dq.back();
    }

    constexpr T &AddBack() {
        dq.template emplace_back(T());
        shift -= 1;
        return Back();
    }

    [[nodiscard]] constexpr size_t GetLastIdx() const {
        return dq.size() - shift;
    }
};

