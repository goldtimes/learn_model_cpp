#include <vector>
#include <unordered_map>
#include <iostream>

using namespace std;

class SolutionHashMap
{
public:
  vector<int> twoSum(vector<int>& nums, int target)
  {
    int i = 0;
    std::unordered_map<int, int> map;

    for (i = 0; i < nums.size(); ++i)
    {
      int value = nums[i];
      auto find_it = map.find(target - value);
      if (find_it != map.end())
      {
        return {i, find_it->second};
      }
      map[nums[i]] = i;
    }
    return {};
  }
};