//
// Created by brostin on 02.04.2022.
//

#include "../core/utils/string_assist.h"
#include "gtest/gtest.h"
#include <string>
#include <string_view>

TEST(replace_chars_test, empty) {
    std::string str;
    EXPECT_EQ(replace_chars(str, '.').size(), 0);
    EXPECT_EQ(replace_chars(str, 'h').size(), 0);
    EXPECT_EQ(replace_chars(str, 'f').size(), 0);
}

TEST(replace_chars_test, all_the_same) {
    for (size_t i = 0; i < 1000 ; i++) {
        std::string str = multiply_string("a", i);
        ASSERT_EQ(replace_chars(str, 'b', 'a'), multiply_string("b", i));
    }

    for (size_t i = 0; i < 1000 ; i++) {
        std::string str = multiply_string("c", i);
        ASSERT_EQ(replace_chars(str, 'b', 'a'), multiply_string("c", i));
    }
}

TEST(replace_chars_test, full) {
    std::string text = "  Change Spaces to   ':'   ";
    std::string expected_spaced = "::Change:Spaces:to:::':':::";
    std::string expected_colon = "  Change Spaces to   ' '   ";
    ASSERT_EQ(replace_chars(text, ':'), expected_spaced);
    ASSERT_EQ(replace_chars(text, ' ', ':'), expected_colon);
}

