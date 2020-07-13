//64. Minimum Path Sum
//1. top left to bottom right
class Solution {
public:
    int minPathSum(vector<vector<int>>& grid) {
        //top left to bottom right
        //time O(mn), space O(n)
        //dp[i][j] = grid[i][j] + min(dp[i-1][j], dp[i][j-1])
	//dp[i][j]表示从grid[0][0]到grid[i][j]的最小值
        if (grid.empty()) return 0;
        int m = grid.size();
        int n = grid[0].size();
        vector<int> dp(n, 0);
        for(int i = 0; i < m; ++i)
        {
            for(int j = 0; j < n; ++j)
            {
                if (j == 0) dp[j] = grid[i][j] + dp[j];
                else if (i == 0) dp[j] = grid[i][j] + dp[j-1];
                else dp[j] = grid[i][j] + min(dp[j], dp[j-1]);
            }
        }
        return dp[n-1];
    }
};
//2. bottom right to top left
class Solution {
public:
    int minPathSum(vector<vector<int>>& grid) {
        //bottom right to top left
        //time O(mn), space O(n)
        //dp[i][j] = grid[i][j] + min(dp[i+1][j], dp[i][j+1])
        //dp[i][j]表示从grid[i][j]到grid[m][n]的最小距离
        if (grid.empty()) return 0;
        int m = grid.size();
        int n = grid[0].size();
        vector<int> dp(n, 0);
        for(int i = m-1; i >= 0; --i)
        {
            for(int j = n-1; j >= 0; --j)
            {
                if (j == n-1) dp[j] = grid[i][j] + dp[j];
                else if (i == m-1) dp[j] = grid[i][j] + dp[j+1];
                else dp[j] = grid[i][j] + min(dp[j], dp[j+1]);
            }
        }
        return dp[0];
    }
};
