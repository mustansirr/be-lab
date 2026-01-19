#include <iostream>
using namespace std;

int main() {
    int n, W;
    cin >> n >> W;   // number of items and capacity

    vector<int> p(n), w(n);
    for(int i = 0; i < n; i++)
        cin >> p[i] >> w[i];   // profit and weight

    vector<vector<int>> dp(n+1, vector<int>(W+1, 0));

    // Build DP table
    for(int i = 1; i <= n; i++){
        for(int cap = 1; cap <= W; cap++){
            if(w[i-1] > cap)
                dp[i][cap] = dp[i-1][cap];  // can't include
            else
                dp[i][cap] = max(dp[i-1][cap], p[i-1] + dp[i-1][cap - w[i-1]]);
        }
    }

    // Backtrack to find selected items
    vector<int> take(n, 0);
    int cap = W;
    for(int i = n; i > 0; i--){
        if(dp[i][cap] != dp[i-1][cap]) {
            take[i-1] = 1;
            cap -= w[i-1];
        }
    }

    cout << "Items taken: ";
    for(int x : take) cout << x << " ";
    cout << "\nMax Profit: " << dp[n][W] << "\n";
}