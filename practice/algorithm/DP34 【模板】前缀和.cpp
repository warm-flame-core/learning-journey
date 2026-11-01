#include <iostream>
#include <vector>
using namespace std;

int main()
{
    // 载入数据
    int n, q;
    cin >> n >> q;
    vector<int> arr(n + 1);
    for (int i = 1; i <= n; i++)
    {
        cin >> arr[i];
    }
    // 预处理前缀和
    vector<long long> dp(n + 1);
    for (int i = 1; i <= n; i++)
    {
        // 可以从前缀和的前一个加上当前的数组快速计算
        dp[i] = dp[i - 1] + arr[i];
    }
    int l, r;
    while (q--)
    {
        // 前缀和相加，r之前的减去l-1之前的即区间的相加值
        cin >> l >> r;
        cout << dp[r] - dp[l - 1] << endl;
    }
    return 0;
}
