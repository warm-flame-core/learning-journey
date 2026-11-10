/*
 * @lc app=leetcode.cn id=191 lang=cpp
 *
 * [191] 位1的个数
 */

// @lc code=start
class Solution
{
public:
    int hammingWeight(int n)
    {
        int cnt = 0;
        while (n)
        {
            // 提取最右边的1，如果提取的出来表示还有1
            if (n & (-n))
            {
                cnt++;
                // 干掉最低位的1
                n &= (n - 1);
            }
        }
        return cnt;
    }
};
// @lc code=end
