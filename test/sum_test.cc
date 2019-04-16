//
// Created by gyun on 2019-04-16.
//

#include <stdio.h>
#include "gtest/gtest.h"

#include "sum.h"

TEST(SUM_TEST/*test case name*/, SUM_TEST_1/*test name*/)
{
  EXPECT_EQ(2, sum(1,1));
}

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
