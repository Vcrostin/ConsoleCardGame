//
// Created by brostin on 12.03.2022.
//

#include "board.h"
#include <random>
#include <chrono>

uint64_t generate_session_id [[deprecated]]() {
    auto now = std::chrono::high_resolution_clock::now();
    std::mt19937_64 random_generator_(now.time_since_epoch().count());
    return random_generator_();
}

Core::Board::Board() {
    cards.resize(12, nullptr);
}

bool Core::Board::StartGameBoard() {
    // TODO: add content
    return false;
}
