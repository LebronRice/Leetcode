// Given a non-empty string, encode the string such that its encoded length is the shortest.

// The encoding rule is: k[encoded_string], where the encoded_string inside the square brackets is being repeated exactly k times.

// Note:

// k will be a positive integer and encoded string will not be empty or have extra space.
// You may assume that the input string contains only lowercase English letters. The string's length is at most 160.
// If an encoding process does not make the string shorter, then do not encode it. If there are several solutions, return any of them is fine.
 

// Example 1:

// Input: "aaa"
// Output: "aaa"
// Explanation: There is no way to encode it such that it is shorter than the input string, so we do not encode it.
 

// Example 2:

// Input: "aaaaa"
// Output: "5[a]"
// Explanation: "5[a]" is shorter than "aaaaa" by 1 character.
 

// Example 3:

// Input: "aaaaaaaaaa"
// Output: "10[a]"
// Explanation: "a9[a]" or "9[a]a" are also valid solutions, both of them have the same length = 5, which is the same as "10[a]".
 

// Example 4:

// Input: "aabcaabcd"
// Output: "2[aabc]d"
// Explanation: "aabc" occurs twice, so one answer can be "2[aabc]d".

// Example 5:

// Input: "abbbabbbcabbbabbbc"
// Output: "2[2[abbb]c]"
// Explanation: "abbbabbbc" occurs twice, but "abbbabbbc" can also be encoded to "2[abbb]c", so one answer can be "2[2[abbb]c]".

// ===================================================================================================================
 
//  Analysis:

//  dp[i][j] means shortest string formed from index i to index j.
// first initialize dp[i][j] to s.substr(i, j - i + 1);
//         for (int len = 1; len <= n; ++len) {	for different potential repetition length
//             for (int i = 0; i + len <= n; ++i) {
// first use a middle index to iterate from i to i + len - 1 to check if dp[i][i  len - 1] could collapse into shorter string
// then int j = i + len to check repetition
// while (j + len <= n && s.compare(i, len, s, j, len) == 0)




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

//dfs with mem:
// class Solution {
//     int n;
//     string em = "";
// public:
//     string encode(string s) {
//         n = s.length();
//         vector<vector<string>> mem(n, vector<string>(n, ""));
//         return helper(s, mem, 0, n - 1);
//     }

//     const string& helper(const string& s, vector<vector<string>>& mem, int i, int j) {
//         if (i > j) return em;
//         if (!mem[i][j].empty()) return mem[i][j];     
//         string cur = s.substr(i, j - i + 1);
//         if (i == j) return mem[i][j] = cur;
//         for (int mid = i; mid < j; ++mid) {
//             const string& s1 = helper(s, mem, i, mid), & s2 = helper(s, mem, mid + 1, j);
//             if (s1.length() + s2.length() < cur.length()) {
//                 cur = s1 + s2;
//             }
//         }
//         for (int len = 1; i + len - 1 < j; ++len) {
//             int k = i + len;
//             int count = 1;
//             const string& s1 = helper(s, mem, i, i + len - 1);
//             while (k + len - 1 <= j && s.compare(i, len, s, k, len) == 0) {
//                 ++count;
//                 k += len;
//                 const string& s2 = helper(s, mem, k, j);
//                 if (s1.length() + to_string(count).length() + 2 + s2.length() < cur.length()) {
//                     cur = to_string(count) + '[' + s1 + ']' + s2;
//                 }
//             }
//         }
//         mem[i][j] = cur;
//         return mem[i][j];
//     }
// };
