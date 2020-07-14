//718. Maximum Length of Repeated Subarray
//最长重复子数组
//1. DP
class Solution {
public:
    int findLength(vector<int>& A, vector<int>& B) {
        //dp[i][j] = dp[i-1][j-1]+1 A[i-1] == B[j-1]
        //         = 0 A[i-1] != B[j-1]
        //time O(mn), space O(mn)
        if (A.empty() || B.empty()) return 0;
        int m = A.size();
        int n = B.size();
        vector<vector<int>> dp(m+1, vector<int>(n+1,0));
        int max_len = 0;
        for(int i=0; i<m+1; ++i)
        {
            for(int j=0; j<n+1; ++j)
            {
                if (i==0 || j==0) continue;
                else if (A[i-1] == B[j-1])
                {
                    dp[i][j] = dp[i-1][j-1]+1;
                    max_len = max(max_len,dp[i][j]);
                }
                else dp[i][j] = 0;
            }
        }
        return max_len;
    }
};

//2. 滑动窗口
class Solution {
        //time O((m+n)*min(m,n)), space O(1)
public:
    int maxLength(vector<int>& A, vector<int>& B, int addA, int addB, int len) {
        int ret = 0, k = 0;
        for (int i = 0; i < len; i++) {
            if (A[addA + i] == B[addB + i]) {
                k++;
            } else {
                k = 0;
            }
            ret = max(ret, k);
        }
        return ret;
    }
    int findLength(vector<int>& A, vector<int>& B) {
        int n = A.size(), m = B.size();
        int ret = 0;
        for (int i = 0; i < n; i++) {
            int len = min(m, n - i);
            int maxlen = maxLength(A, B, i, 0, len);
            ret = max(ret, maxlen);
        }
        for (int i = 0; i < m; i++) {
            int len = min(n, m - i);
            int maxlen = maxLength(A, B, 0, i, len);
            ret = max(ret, maxlen);
        }
        return ret;
    }
};
