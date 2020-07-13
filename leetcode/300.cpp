//300. Longest Increasing Subsequence
//最长上升子序列 LIS

//1. DP
class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        //dp[i]代表以第i个数字为结尾的最长上升子序列的长度
        //dp[i] = max(dp[i], dp[j] + 1 if nums[j] < nums[i])
	//time O(n^2), space O(n)
        if (nums.empty()) return 0;
        int ret = 1;
        vector<int> dp(nums.size(), 1);//mention that init 1!
        for (int i = 1; i < nums.size(); ++i)
        {
            for (int j = 0; j < i; ++j)
            {
                if (nums[j] < nums[i])
                    dp[i] = max(dp[i], dp[j]+1);
            }
            ret = max(ret, dp[i]);
        }
        return ret;
    }
};
