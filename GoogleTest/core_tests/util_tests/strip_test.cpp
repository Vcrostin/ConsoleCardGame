//
// Created by brostin on 02.04.2022.
//

#include "../../../core/utils/string_assist.h"
#include "gtest/gtest.h"
#include <string_view>
#include <string>

TEST(test_strip, empty) {
    std::string str;
    ASSERT_EQ(string_strip(str).size(), 0);
    ASSERT_EQ(string_strip(str, ':').size(), 0);
}

TEST(test_strip, all_delim) {
    std::string str = "    ";
    std::string str_d = "::::::";
    std::string str_p = ".";
    EXPECT_EQ(string_strip(str).size(), 0);
    EXPECT_EQ(string_strip(str_d, ':').size(), 0);
    EXPECT_EQ(string_strip(str_p, '.').size(), 0);
}

TEST(test_strip, basic_test) {
    std::string str1 = "   this    is    text   ";
    std::string str2 = "   this    is    text";
    std::string str3 = "this    is    text    ";
    std::string str_expected = "this    is    text";
    EXPECT_EQ(string_strip(str1), str_expected);
    EXPECT_EQ(string_strip(str2), str_expected);
    EXPECT_EQ(string_strip(str3), str_expected);
}

TEST(test_strip, basic_test_delim) {
    std::string str1 = ":::this    is    text:::";
    std::string str2 = "...this    is    text";
    std::string str3 = "this    is    text-----";
    std::string str4 = "  this    is    text  ";
    std::string str_expected = "this    is    text";
    EXPECT_EQ(string_strip(str1, ':'), str_expected);
    EXPECT_EQ(string_strip(str2, '.'), str_expected);
    EXPECT_EQ(string_strip(str3, '-'), str_expected);
    EXPECT_EQ(string_strip(str4, '-'), str4);
}

TEST(test_strip, same_input_string_view) {
    std::string str = "here   this    is    text    ";
    auto str_v = std::string_view(str);
    str_v.remove_prefix(4);
    std::string_view expected_str_v = "   this    is    text    ";
    std::string expected_res = "this    is    text";
    ASSERT_EQ(str_v, expected_str_v);
    EXPECT_EQ(string_strip(str_v), expected_res);
    ASSERT_EQ(str_v, expected_str_v);
}

TEST(test_strip, same_input_string_view_with_delim) {
    std::string str = "here___this___is___text___";
    auto str_v = std::string_view(str);
    str_v.remove_prefix(4);
    std::string_view expected_str_v = "___this___is___text___";
    std::string expected_res = "this___is___text";
    ASSERT_EQ(str_v, expected_str_v);
    EXPECT_EQ(string_strip(str_v, '_'), expected_res);
    ASSERT_EQ(str_v, expected_str_v);
}
