#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>

using namespace std;

int MinTotalLength(const vector<int>& sortNails) {
    int n = sortNails.size();
    vector<int> dp(n, 0);
    dp[1] = sortNails[1] - sortNails[0];
    dp[2] = dp[1] + sortNails[2] - sortNails[1];
    for (int i = 3; i < n; i++) {
        dp[i] = min(dp[i - 1] + sortNails[i] - sortNails[i - 1], dp[i - 2] + sortNails[i] - sortNails[i - 1]);
    }
    return dp[n - 1];
}

int main() {
    int n;
    cin >> n;
    vector<int> nails(n);
    for (int i = 0; i < n; i++) {
        cin >> nails[i];
    }
    vector<int> sortNails = nails;
    sort(sortNails.begin(), sortNails.end());
    int result = MinTotalLength(sortNails);
    cout << result << endl;
    return 0;
}