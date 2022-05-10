#include "dynamic_array.h"
#include "gtest/gtest.h"
#include <array>
#include <vector>

TEST(dynamic_array_test_size, AllCases) {
  stl_complement::dynamic_array<int> array(2);
  EXPECT_EQ(array.size(), 2);
  EXPECT_EQ(array.max_size(), 2);
}

TEST(dynamic_array__test_default_constructor, AllCases) {
  stl_complement::dynamic_array<int> array(5);
  array[0] = 0;
  array[1] = 1;
  array[2] = 2;
  array[3] = 3;
  array[4] = 4;
  array[5] = 5;

  for (auto i = 0; i < array.size(); ++i) {
    EXPECT_EQ(array[i], i);
  }
}

TEST(dynamic_array__test_operator_equality, AllCases) {
  constexpr std::size_t loop_times = 50000;
  for (auto i = 0; i < loop_times; ++i) {
    stl_complement::dynamic_array<int> array(i);
    stl_complement::dynamic_array<int> another_array(i);
    stl_complement::dynamic_array<int> another_not_equal_array(i);
    for (auto k = 0; k < array.size(); ++k) {
      // TODO a better option would be assign the array with random value
      array[k] = k;
      another_array[k] = k;
      another_not_equal_array[k] = k;
    }
    EXPECT_TRUE(array == array);

    ASSERT_TRUE(array == another_array);

    ASSERT_TRUE(another_array == another_array);
    ASSERT_TRUE(another_array == array);

    if (i > 0) {
      another_not_equal_array[0] = -1; // change one member on purpose

      ASSERT_NE(array, another_not_equal_array);
      ASSERT_NE(another_array, another_not_equal_array);

      ASSERT_TRUE(another_not_equal_array == another_not_equal_array);
      ASSERT_TRUE(another_not_equal_array != array);
      ASSERT_TRUE(another_not_equal_array != another_array);
    }
  }
}

TEST(dynamic_array__test_assign_operator, AllCases) {
  for (std::size_t size = 0; size < 50000; ++size) {
    stl_complement::dynamic_array<int> array(size);
    for (auto &ele : array) {
      ele = size*19 % 17; // I just set it randomly
    }
    stl_complement::dynamic_array<int> another_array(array);
    ASSERT_TRUE(array == another_array);
  }
}