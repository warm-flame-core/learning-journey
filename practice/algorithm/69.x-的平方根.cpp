/*
 * @lc app=leetcode.cn id=69 lang=cpp
 *
 * [69] x 的平方根
 */

// @lc code=start
class Solution
{
public:
    int mySqrt(int x)
    {
        if (x < 1)
            return 0;
        if (x == 1)
            return 1;
        int left = 1;
        int right = x;
        while (left < right)
        {
            // 用longlong防止溢出，同时用模板有减法要加一
            long long mid = left + (right - left + 1) / 2;
            if (mid * mid <= x)
            {
                left = mid;
            }
            else
            {
                right = mid - 1;
            }
        }
        return left;
    }
};
// @lc code=end
