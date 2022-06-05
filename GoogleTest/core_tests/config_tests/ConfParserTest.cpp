//
// Created by brostin on 06.06.22.
//

#include "gtest/gtest.h"
#include <string>
#include "../../../core/configurations/conf_parser.h"


TEST(conf_tests, non_empty_stream_general) {
    ConfParser parser(CONF_PATH + "/general.cfg");
    EXPECT_NO_THROW(parser.GetInt("maxPackageSize"));
    ASSERT_GT(parser.GetInt("maxPackageSize"), 1);
}