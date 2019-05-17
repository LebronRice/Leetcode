class Solution {
public:
    string encode(string s) {
        const int n = s.length();
        vector<vector<string>> dp(n, vector<string>(n, "")); 
        for (int i = 0; i < n; ++i) {
            for (int j = i; j < n; ++j) {
                dp[i][j] = s.substr(i, j - i + 1);
            }
        }
        for (int len = 1; len <= n; ++len) {
            for (int i = 0; i + len <= n; ++i) {
                for (int mid = i; mid < i + len - 1; ++mid) {
                    if (dp[i][mid].length() + dp[mid + 1][i + len - 1].length() < dp[i][i + len - 1].length()) {
                        dp[i][i + len - 1] = dp[i][mid] + dp[mid + 1][i + len - 1];
                    }
                }
                int j = i + len;
                int count = 1;
                while (j + len <= n && s.compare(i, len, s, j, len) == 0) {
                    ++count;
                    j += len;
                    if (dp[i][i + len - 1].length() + to_string(count).length() + 2 < dp[i][j - 1].length()) {                        
                        dp[i][j - 1] = to_string(count) + '[' + dp[i][i + len - 1] + ']';
                    }                    
                }
                    
            }
        }
        return dp[0][n - 1];
    }
};
