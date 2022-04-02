//
// Created by brostin on 02.04.2022.
//

#include "../core/utils/string_assist.h"
#include "gtest/gtest.h"
#include <string>
#include <string_view>

TEST(test_string_split, test_splitted_string_empty1) {
    std::string str;
    EXPECT_EQ(string_split(str).size(), 0);
}

TEST(test_string_split, test_splitted_string_empty1_with_custom_delim) {
    std::string str;
    EXPECT_EQ(string_split(str, ':').size(), 0);
}

TEST(test_string_split, test_splitted_string_empty2) {
    std::string str = " ";
    EXPECT_EQ(string_split(str).size(), 0);
}

TEST(test_string_split, test_splitted_string_empty2_with_custom_delim) {
    std::string str = ":";
    EXPECT_EQ(string_split(str, ':').size(), 0);
}

TEST(test_string_split, test_splitted_string_empty3) {
    std::string str = "     ";
    EXPECT_EQ(string_split(str).size(), 0);
}

TEST(test_string_split, test_splitted_string_empty3_with_custom_delim) {
    std::string str = ":::::";
    EXPECT_EQ(string_split(str, ':').size(), 0);
}

TEST(test_string_split, test_splitted_string_not_splitted1) {
    std::string str = "abcdef";
    auto split_str = string_split(str);
    ASSERT_EQ(split_str.size(), 1);
    EXPECT_EQ(split_str[0], str);
}

TEST(test_string_split, test_splitted_string_not_splitted2) {
    std::string str = "c";
    auto split_str = string_split(str);
    ASSERT_EQ(split_str.size(), 1);
    EXPECT_EQ(split_str[0], str);
}

TEST(test_string_split, test_splitted_string_to_parts1) {
    std::string str = "abcdef abcdef";
    std::vector string_expected = {"abcdef", "abcdef"};
    auto split_str = string_split(str);
    ASSERT_EQ(split_str.size(), string_expected.size());

    // TODO: zip function
    for (size_t i = 0; i < string_expected.size(); i++) {
        ASSERT_EQ(string_expected[i], split_str[i]);
    }
}

TEST(test_string_split, test_splitted_string_to_parts2) {
    std::string str = "   abcdef    abcdef   ";
    std::vector string_expected = {"abcdef", "abcdef"};
    auto split_str = string_split(str);
    ASSERT_EQ(split_str.size(), string_expected.size());

    // TODO: zip function
    for (size_t i = 0; i < string_expected.size(); i++) {
        ASSERT_EQ(string_expected[i], split_str[i]);
    }
}

TEST(test_string_split, test_splitted_string_to_parts_with_custom_delim1) {
    std::string str = "abcdef:abcdef";
    std::vector string_expected = {"abcdef", "abcdef"};
    auto split_str = string_split(str, ':');
    ASSERT_EQ(split_str.size(), string_expected.size());

    // TODO: zip function
    for (size_t i = 0; i < string_expected.size(); i++) {
        ASSERT_EQ(string_expected[i], split_str[i]);
    }
}

TEST(test_string_split, test_splitted_string_to_parts_with_custom_delim2) {
    std::string str = ":::abcdef::::abcdef:::::::";
    std::vector string_expected = {"abcdef", "abcdef"};
    auto split_str = string_split(str, ':');
    ASSERT_EQ(split_str.size(), string_expected.size());

    // TODO: zip function
    for (size_t i = 0; i < string_expected.size(); i++) {
        ASSERT_EQ(string_expected[i], split_str[i]);
    }
}

TEST(test_string_split, test_multi_splitted_string_to_parts) {
    std::string str = " a    b c    d e   f a    b c d     e f  ";
    std::vector string_expected = {"a","b","c","d","e","f", "a","b","c","d","e","f"};
    auto split_str = string_split(str);
    ASSERT_EQ(split_str.size(), string_expected.size());

    // TODO: zip function
    for (size_t i = 0; i < string_expected.size(); i++) {
        ASSERT_EQ(string_expected[i], split_str[i]);
    }
}

TEST(test_string_split, test_multi_splitted_string_to_parts_with_custom_delim) {
    std::string str = ":a::::b::c:::d::e::::f::a::::b:c::d::::e:f:";
    std::vector string_expected = {"a","b","c","d","e","f", "a","b","c","d","e","f"};
    auto split_str = string_split(str, ':');
    ASSERT_EQ(split_str.size(), string_expected.size());

    // TODO: zip function
    for (size_t i = 0; i < string_expected.size(); i++) {
        ASSERT_EQ(string_expected[i], split_str[i]);
    }
}
