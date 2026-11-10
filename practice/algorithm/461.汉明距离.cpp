/*
 * @lc app=leetcode.cn id=461 lang=cpp
 *
 * [461] 汉明距离
 */

// @lc code=start
class Solution
{
public:
    int hammingDistance(int x, int y)
    {
        // 根据异或运算法则，相同为0，不同为1，满足题目要求
        int s = x ^ y;
        int ret;
        // 疑惑之后检查1的个数就可以了
        while (s)
        {
            ret += s & 1;
            s >>= 1;
        }

        return ret;
    }
};
// @lc code=end
