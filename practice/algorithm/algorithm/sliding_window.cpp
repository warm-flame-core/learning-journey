//滑动窗口
#include "head.h"

// 力扣209
// 给定一个含有 n 个正整数的数组和一个正整数 target 。
// 找出该数组中满足其总和大于等于 target 的长度最小的 子数组[numsl, numsl + 1, ..., numsr - 1, numsr] ，并返回其长度。如果不存在符合条件的子数组，返回 0 。
// 最坏的情况是两边都要走一遍，n+n是2n，时间复杂度是o(n)，不能看到两层循环就认为是o(n*n)
class Solution {
public:
    int minSubArrayLen(int target, vector<int>& nums) {
        int n = nums.size();
        int left = 0;
        int right = 0;
        int ret = INT_MAX;
        int sum = 0;
        for (left = 0, right = 0; right < n; right++)
        {
            sum += nums[right];     // 记录右边数据
            while (sum >= target)   // 如果达到要求就减小窗口
            {
                ret = min(ret, right - left + 1);   // 缩短窗口之后长度要减少
                sum -= nums[left++];    // 左边缩短就要扔掉左边的窗口
            }

        }
        return ret == INT_MAX ? 0 : ret;
    }
};