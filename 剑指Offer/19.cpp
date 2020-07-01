//剑指 Offer 19. 正则表达式匹配
//1. DP
//https://leetcode-cn.com/problems/zheng-ze-biao-da-shi-pi-pei-lcof/solution/zhu-xing-xiang-xi-jiang-jie-you-qian-ru-shen-by-je/
class Solution {
public:
    bool isMatch(string s, string p) {
        //time O(mn), space O(mn)
        int m = s.length();
        int n = p.length();
        bool dp[m+1][n+1];
        //cout<<m<<","<<n<<endl;        
        for(int i=0; i<= m; ++i)
            memset(dp[i],false,(n+1)*sizeof(bool));        
        for (int i = 0; i <= m; ++i)
        {
            for (int j = 0; j <= n; ++j)
            {
                cout<<i<<","<<j<<endl;
                if (j == 0)
                    dp[i][j] = (i == 0);
                else
                {
                    if (p[j-1] != '*')
                    {
                        if (i >= 1 && (s[i-1] == p[j-1] || p[j-1] == '.'))
                            dp[i][j] = dp[i][j] || dp[i-1][j-1];
                    }
                    else
                    {
                        if (j >= 2)
                            dp[i][j] = dp[i][j] || dp[i][j-2];
                        if (i >= 1 && (j >= 2 && s[i-1] == p[j-2] || p[j-2] == '.'))
                            dp[i][j] = dp[i][j] || dp[i-1][j];
                    }
                }
            }
        }
        return dp[m][n];
    }
};

//2.递归
//https://leetcode-cn.com/problems/zheng-ze-biao-da-shi-pi-pei-lcof/solution/zheng-ze-biao-da-shi-pi-pei-di-gui-qiu-jie-by-jarv/
class Solution {
public:
    bool isMatch(string s, string p) {
        if (p.empty()) return s.empty();
        if (p[1] == '*')
        {
            return isMatch(s,p.substr(2)) || (!s.empty() && (s[0] == p[0] || p[0] == '.') && isMatch(s.substr(1), p));
        }
        else
        {
            return !s.empty() && (s[0] == p[0] || p[0] == '.') && (isMatch(s.substr(1), p.substr(1)));
        }
    }
};
