#include <iostream>
#include <vector>
using namespace std;

int main()
{
    int n, m, q;
    cin >> n >> m >> q;
    vector<vector<int>> arr(n + 1, vector<int>(m + 1));
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            cin >> arr[i][j];
        }
    }
    vector<vector<long long>> dp(n + 1, vector<long long>(m + 1));
    // 预处理前缀和数组：面积法
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            dp[i][j] = dp[i - 1][j] + dp[i][j - 1] - dp[i - 1][j - 1] + arr[i][j];
        }
    }
    int x1, y1, x2, y2;
    while (q--)
    {
        // 还是面积法
        cin >> x1 >> y1 >> x2 >> y2;
        cout << dp[x2][y2] - dp[x1 - 1][y2] - dp[x2][y1 - 1] + dp[x1 - 1][y1 - 1] << endl;
    }
    return 0;
}
// 64 位输出请用 printf("%lld")
