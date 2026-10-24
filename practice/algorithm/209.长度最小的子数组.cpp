/*
 * @lc app=leetcode.cn id=209 lang=cpp
 *
 * [209] 长度最小的子数组
 */

// @lc code=start
class Solution
{
  public:
    int minSubArrayLen(int target, vector<int> &nums)
    {
        int n = nums.size();
        int left = 0;
        int right = 0;
        int ret = INT_MAX;
        int sum = 0;
        for (left = 0, right = 0; right < n; right++)
        {
            sum += nums[right];
            while (sum >= target)
            {
                ret = min(ret, right - left + 1);
                sum -= nums[left++];
            }
        }
        return ret == INT_MAX ? 0 : ret;
    }
};
// @lc code=end
