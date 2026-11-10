/*
 * @lc app=leetcode.cn id=338 lang=cpp
 *
 * [338] 比特位计数
 */

// @lc code=start
class Solution
{
public:
    vector<int> countBits(int n)
    {
        vector<int> v;
        for (int i = 0; i <= n; i++)
        {
            int cnt = 0;
            int m = i;
            while (m)
            {
                if (m & (-m))
                {
                    cnt++;
                    m &= (m - 1);
                }
            }
            v.push_back(cnt);
        }
        return v;
    }
};
// @lc code=end
