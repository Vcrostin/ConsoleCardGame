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
    cur_user = std::make_unique<User>(generate_session_id(), "name1", 0);
    opponent_user = std::make_unique<User>(generate_session_id(), "name2", 0);
}
