//leetcode 343. Integer Break
//剑指 Offer 14- I. 剪绳子
//1. DP
class Solution {
public:
    int cuttingRope(int n) {
        //if (n <= 0) return 0;
        //time O(n^2), space O(n)
        vector<int> dp(n+1,0);
        dp[1] = 1, dp[2] = 1;
        for (int i = 3; i <= n; ++i)
        {
            for (int j = 1; j < i; ++j)
                dp[i] = max(dp[i], max(j*(i-j), j*dp[i-j]));
        }
        return dp[n];
    }
};

//2. DP
class Solution {
public:
    int cuttingRope(int n) {
        //time O(n), space O(1)
        vector<int> dp = {0, 1, 1};
        for (int i = 3; i <= n; ++i)
        {
            dp[i%3] = max(max(dp[(i-1)%3], i-1),
                        max(2*max(dp[(i-2)%3], i-2),
                            3*max(dp[i%3], i-3)));
        }
        return dp[n%3];
    }
};

//3. Math
class Solution {
public:
    int cuttingRope(int n) {
        //time O(1), space O(1)
        if (n <= 3) return n-1;
        int a = n/3, b = n%3;
        if (b == 0) return pow(3,a);
        if (b == 1) return pow(3,a-1)*4;
        if (b == 2) return pow(3,a)*2;
        return -1;
    }
};
