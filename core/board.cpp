//
// Created by brostin on 12.03.2022.
//

#include "board.h"
#include <random>
#include <chrono>

uint64_t generate_session_id() {
    auto now = std::chrono::high_resolution_clock::now();
    std::mt19937_64 random_generator_(now.time_since_epoch().count());
    return random_generator_();
}

Core::Board::Board() {
    cards.resize(12, nullptr);
    firstUser = nullptr;
    secondUser = nullptr;
}

bool Core::Board::AddUser(const Core::User &user) {
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

bool Core::Board::IsBusy() const {
    return !(firstUser == nullptr && secondUser == nullptr);
}

bool Core::Board::StartGameBoard() {
    // TODO: add content
    return false;
}
