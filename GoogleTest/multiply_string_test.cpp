//
// Created by brostin on 02.04.2022.
//

#include "../core/utils/string_assist.h"
#include "gtest/gtest.h"
#include <string>
#include <string_view>

TEST(multiply_string_test, empty) {
    std::string str;
    for (size_t i = 0; i < 1000; i++) {
        ASSERT_EQ(multiply_string(str, i).size(), 0);
    }
}

TEST(multiply_string_test, basic_single) {
    std::string str = "a";
    for (size_t i = 0; i < 1000; i++) {
        auto mp = multiply_string(str, i);
        ASSERT_EQ(mp.size(), str.size() * i);
        for (size_t j = 0; j < mp.size(); j+= str.size()) {
            for (size_t k = j; k < j + str.size(); k++) {
                ASSERT_EQ(str[k % str.size()], mp [k]);
            }
        }
    }
}

TEST(multiply_string_test, basic_multi) {
    std::string str = "abcd";
    for (size_t i = 0; i < 1000; i++) {
        auto mp = multiply_string(str, i);
        ASSERT_EQ(mp.size(), str.size() * i);
        for (size_t j = 0; j < mp.size(); j+= str.size()) {
            for (size_t k = j; k < j + str.size(); k++) {
                ASSERT_EQ(str[k % str.size()], mp [k]);
            }
        }
    }
}
