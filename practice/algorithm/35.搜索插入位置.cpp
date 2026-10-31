/*
 * @lc app=leetcode.cn id=35 lang=cpp
 *
 * [35] 搜索插入位置
 */

// @lc code=start
class Solution
{
public:
    int searchInsert(vector<int>& nums, int target)
    {
        int left = 0;
        int right = nums.size() - 1;
        while (left < right)
        {
            // 两个判断都没有减法，套模板不需要向上取整加1
            int mid = left + (right - left) / 2;
            if (nums[mid] >= target)
            {
                right = mid;
            }
            else
            {
                left = mid + 1;
            }
        }
        // 单独处理，如果说相遇之后取值还是小于目标值，说明目标值应该插入到数组的最后面
        if (nums[left] < target)
            return left + 1;
        return left;
    }
};
// @lc code=end
