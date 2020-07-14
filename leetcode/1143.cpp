//1143. Longest Common Subsequence
//最长公共子序列
class Solution {
public:
    int longestCommonSubsequence(string text1, string text2) {
        //dp[i][j] = dp[i-1][j-1]+1 text1[i-1] == text2[j-1]
        //         = max(dp[i-1][j],dp[i][j-1]) text1[i-1] != text2[j-1]
        //time O(mn), space O(mn)
        if (text1.empty()||text2.empty()) return 0;
        int m = text1.length();
        int n = text2.length();
        vector<vector<int>> dp(m+1, vector<int>(n+1,0));
        for(int i=0; i<m+1; ++i)
        {
            for(int j=0; j<n+1; ++j)
            {
                if (i==0 || j==0) continue;
                else if (text1[i-1] == text2[j-1]) dp[i][j] = dp[i-1][j-1]+1;
                else dp[i][j] = max(dp[i-1][j],dp[i][j-1]);
            }
        }
        return dp[m][n];
    }
};
