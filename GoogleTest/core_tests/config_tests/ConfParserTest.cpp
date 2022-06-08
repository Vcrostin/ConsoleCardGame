//
// Created by brostin on 06.06.22.
//

#include "gtest/gtest.h"
#include <string>
#include "../../../core/utils/path_manip.h"
#include "../../../core/configurations/conf_parser.h"


TEST(conf_tests, int_config_check) {
    ConfParser parser(PathManip().GetCurPath() + "/general.cfg");
    EXPECT_NO_THROW(parser.GetInt("int_value"));
    EXPECT_NO_THROW(parser.GetInt("int_value2"));
    ASSERT_EQ(parser.GetInt("int_value"), 1000);
    ASSERT_EQ(parser.GetInt("int_value2"), 1010);
}

TEST(conf_tests, string_config_check) {
    ConfParser parser(PathManip().GetCurPath() + "/general.cfg");
    EXPECT_NO_THROW(parser.GetString("string_value"));
    EXPECT_NO_THROW(parser.GetString("string_value2"));
    ASSERT_EQ(parser.GetString("string_value"), "expected");
    ASSERT_EQ(parser.GetString("string_value2"), "new_string");
}
