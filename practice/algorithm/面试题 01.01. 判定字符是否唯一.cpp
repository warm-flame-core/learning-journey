class Solution
{
public:
    bool isUnique(string astr)
    {
        if (astr.size() > 26)
            return false;
        int n = 0;
        for (auto e : astr)
        {
            // 字母的哈希位置
            int nums = e - 'a';
            // 如果检测位图发现已经在对应位置上有1了，说明重复了
            if ((n >> nums) & 1)
            {
                return false;
            }
            else
            {
                n |= (1 << nums);
            }
        }
        return true;
    }
};
