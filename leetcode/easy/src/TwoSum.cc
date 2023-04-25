#include <vector>
#include <unordered_map>
#include <iostream>

using namespace std;

class Solution
{
public:
  vector<int> twoSum(vector<int>& nums, int target)
  {
    int i = 0, j = 0;
    std::vector<int> result;
    for (i = 0; i < nums.size() - 1; ++i)
    {
      for (j = i + 1; j < nums.size(); ++j)
      {
        if (nums[i] + nums[j] == target)
        {
          result.push_back(i);
          result.push_back(j);
          return result;
        }
        else
          continue;
      }
    }
    return result;
  }
};