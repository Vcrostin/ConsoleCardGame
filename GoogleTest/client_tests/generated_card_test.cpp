//
// Created by brostin on 22.06.22.
//

#include "gtest/gtest.h"
#include "../../core/card_types/generated_cards/all_generated_classes.h"

TEST(generated_card_test, check_size) {
    ASSERT_GT(GeneratedCard::HashTable.size(), 0);
}

TEST(generated_card_test, no_throw_classes) {
    for (auto &[k, v]: GeneratedCard::HashTable) {
        ASSERT_NO_THROW(v());
    }
}
