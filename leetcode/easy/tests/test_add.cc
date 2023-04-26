#include "../src/TwoSum.cc"
#include "../src/TwoSumHashCode.cc"
#include "gtest/gtest.h"

namespace
{
  GTEST_TEST(Solution, test_two_sum)
  {
    std::vector<int> input_datas{1, 2, 3};
    const int target = 5;
    Solution s;
    auto result = s.twoSum(input_datas, 5);
    for (const auto index : result)
    {
      std::cout << "index: " << index << " ";
    }
    EXPECT_EQ(2, result.size())
        << "index_1: " << result[0] << "index_2:" << result[1] << std::endl;
  }

  GTEST_TEST(SolutionHashMap, test_two_sum)
  {
    std::vector<int> input_datas{1, 2, 3};
    const int target = 5;
    Solution s;
    auto result = s.twoSum(input_datas, 5);
    for (const auto index : result)
    {
      std::cout << "index: " << index << " ";
    }
    EXPECT_EQ(2, result.size())
        << "index_1: " << result[0] << "index_2:" << result[1] << std::endl;
  }
} // namespace
