//120. Triangle
//1. DP, bottom to top
class Solution {
public:
    int minimumTotal(vector<vector<int>>& triangle) {
        //time O(n^2), space O(n)
        //dp[i][j] = triangle[i][j] + min(dp[i+1][j], dp[i+1][j+1]);
        if (triangle.empty()) return 0;
        vector<int> dp(triangle.back());
        for (int i = triangle.size()-2; i >= 0; --i)
        {
            for (int j = 0; j <= i; ++j)
                dp[j] = triangle[i][j] + min(dp[j], dp[j+1]);
        }
        return dp[0];
    }
};

//2. DP, top to bottom
class Solution {
public:
    int minimumTotal(vector<vector<int>>& triangle) {
        //time O(n^2), space O(n^2)
        vector<vector<int>> r;//和数组
        r.resize(triangle.size());
        for(int i=0;i<triangle.size();i++){
                r[i].resize(triangle[i].size(),0);
            }
        r[0][0] = triangle[0][0];
        for(int i=1;i<triangle.size();i++){
            for(int j=0;j<triangle[i].size();j++){
                if(j==0)//i行第一个
                    r[i][j]=r[i-1][j]+triangle[i][j];
                else if(j==triangle[i].size()-1)//i行最后一个
                    r[i][j]=r[i-1][j-1]+triangle[i][j];
                else//中间部分
                    r[i][j] = min(r[i-1][j-1],r[i-1][j])+triangle[i][j];
            }
        }
        return *min_element(r.back().begin(),r.back().end());
    }
};

