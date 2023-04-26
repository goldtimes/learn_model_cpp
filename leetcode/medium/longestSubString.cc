#include <iostream>
#include <string>
#include <unordered_map>

class Solution
{
public:
  int lengthOfLongestSubstringHashMap(const std::string& s)
  {
    int start = 0;
    int end = 0;
    int length = 0;
    int result = 0;
    std::unordered_map<char, int> hash{};
    for (int i = 0; i < s.size(); i++)
    {
      char ch = s[i];
      if (hash.find(ch) != hash.end() &&
          hash[ch] >= start) // find in the hashmap
      {
        start = hash[ch] + 1;
        length = end - start;
      }
      // update hash
      hash[ch] = i;
      end++;
      length++;
      result = std::max(result, length);
    }
    return result;
  }

  int lengthOfLongestSubstringSlidWindow(const std::string& s)
  {
    int start = 0; // 左边界指针
    int end = 0;   // 右边界指针
    int length = 0;
    int result = 0;
    int size = s.size();
    while (end < size)
    {
      char ch = s[end];
      // 判断 ch 是否在[start,end)的半区间中是否存在
      for (int index = start; index < end; ++index)
      {
        // 如果存在
        if (ch == s[index])
        {
          // 左区间调整到重复的元素前一个
          start = index + 1;
          // 调整长度
          length = end - start;
          break;
        }
      }
      end++;    // 右边边界先递增
      length++; // 长度也要递增
      result = std::max(result, length);
    }
  }
};

int main(int argc, char** argv)
{
  std::string s1 = "abcabcbb";
  std::string s2 = "bbbbb";
  std::string s3 = "pwwkew";

  return 0;
}