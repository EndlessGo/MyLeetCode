//674. Longest Continuous Increasing Subsequence
//1. 暴力法
class Solution {
public:
    int findLengthOfLCIS(vector<int>& nums) {
        //time O(n), space O(1)
        if (nums.empty()) return 0;
        int len = 1;
        int max_len = 1;
        for (int i = 1; i < nums.size(); ++i)
        {
            if (nums[i-1] < nums[i])
                ++len;
            else
                len =1;
            max_len = max(max_len, len);
        }
        return max_len;
    }
};

//2. DP
class Solution {
public:
    int findLengthOfLCIS(vector<int>& nums) {
        //dp[i]表示位置i的连续递增子序列长度，初始化为1，因为每个数字是最小的递增子序列
        //状态转移方程：若nums[i-1]<nums[i]，则dp[i]=dp[i-1]+1；否则dp[i]=1
        //time O(n), space O(n)
        if(nums.empty())return 0;
        int res=1,n=nums.size();
        vector<int> dp(n,1);
        for(int i=1;i<n;++i)
        {
            if(nums[i]>nums[i-1])dp[i]=dp[i-1]+1;
            res=max(res,dp[i]);
        }
        return res;
    }
};
