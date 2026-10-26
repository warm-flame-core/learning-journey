/*
 * @lc app=leetcode.cn id=34 lang=cpp
 *
 * [34] 在排序数组中查找元素的第一个和最后一个位置
 */

// @lc code=start
class Solution
{
public:
    vector<int> searchRange(vector<int>& nums, int target)
    {
        // 寻找两个端点时的循环不能用等于，不然等于的时候两种端点都会死循环
        if (nums.empty())
            return {-1, -1};
        int left = 0;
        int right = nums.size() - 1;
        // 寻找左端点
        while (left < right)
        {
            // 求中点用不会溢出的方法，而且只能用向下取整，因为如果向上取整时right会不动也会死循环
            int mid = left + (right - left) / 2;
            if (nums[mid] < target)
                left = mid + 1;
            else
                right = mid;
        }
        // 出循环时right和left一定时相等的
        // 需要先判断相等时是否时targe值，不是就为没有结果
        if (nums[left] != target)
            return {-1, -1};

        // 记录左端点
        int begin = left;
        // 寻找右端点
        // left可以优化，从从左边端点开始查找
        right = nums.size() - 1;
        while (left < right)
        {
            // 同理防止死循环
            int mid = left + (right - left + 1) / 2;
            if (nums[mid] <= target)
                left = mid;
            else
                right = mid - 1;
        }
        return {begin, right};
    }
};
// @lc code=end
