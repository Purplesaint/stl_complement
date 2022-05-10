#include "dynamic_array.h"
#include "gtest/gtest.h"

TEST(dynamic_array__Test,AllCases)
{
    stl_complement::dynamic_array<int> array(2);
    EXPECT_EQ(array.size(), 2);
    EXPECT_EQ(array.max_size(), 2);
}