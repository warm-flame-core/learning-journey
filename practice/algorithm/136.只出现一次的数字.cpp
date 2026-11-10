/*
 * @lc app=leetcode.cn id=136 lang=cpp
 *
 * [136] 只出现一次的数字
 */

// @lc code=start
class Solution
{
public:
    int singleNumber(vector<int>& nums)
    {
        int ret = 0;
        for (auto e : nums)
        {
            // 因为异或运算与顺序无关，而且相同两数异或运算为0
            // 只出现一次的数异或还是本身
            ret ^= e;
        }
        return ret;
    }
};
// @lc code=end
