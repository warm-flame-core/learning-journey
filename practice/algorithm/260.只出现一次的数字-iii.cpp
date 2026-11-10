/*
 * @lc app=leetcode.cn id=260 lang=cpp
 *
 * [260] 只出现一次的数字 III
 */

// @lc code=start
class Solution
{
public:
    vector<int> singleNumber(vector<int>& nums)
    {
        int ret = 0;
        vector<int> g1;
        vector<int> g2;
        vector<int> g3;
        // 先将所有数组异或一遍，这样的话ret = x ^ y
        for (auto e : nums)
        {
            ret ^= e;
        }
        // 可以发现，异或之后某一位如果是1说明那一位上两个数相异，由此可以吧数分类为两组，而且两个所求一定在两个组里
        // 再用一次异或分别提纯就好了
        int key = ret & (-(long long)ret);
        for (auto e : nums)
        {
            if (e & key)
            {
                g1.push_back(e);
            }
            else
            {
                g2.push_back(e);
            }
        }
        ret = 0;
        for (auto e : g1)
        {
            ret ^= e;
        }
        g3.push_back(ret);
        ret = 0;
        for (auto e : g2)
        {
            ret ^= e;
        }
        g3.push_back(ret);
        return g3;
    }
};
// @lc code=end
