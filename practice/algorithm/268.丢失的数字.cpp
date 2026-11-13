/*
 * @lc app=leetcode.cn id=268 lang=cpp
 *
 * [268] 丢失的数字
 */

// @lc code=start
class Solution
{
public:
    int missingNumber(vector<int>& nums)
    {
        // 异或一遍数组和0到N的数字，运用消消乐可以只得到只出现一次的
        int ret = 0;
        for (auto e : nums)
        {
            ret ^= e;
        }
        for (int i = 0; i <= nums.size(); i++)
        {
            ret ^= i;
        }
        return ret;
    }
};
class Solution
{
public:
    int missingNumber(vector<int>& nums)
    {
        // 高斯求和，求和本来应该在的减去重复的就是只出现一次的
        int ret = (nums.size()) * (nums.size() + 1) / 2;
        for (auto e : nums)
        {
            ret -= e;
        }
        return ret;
    }
};
// @lc code=end
