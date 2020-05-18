//62.Unique Paths
class Solution {
public:
    int uniquePaths(int m, int n) {
        if (m > n)
            return uniquePaths(n,m);
        vector<int> result(m,1);
        for (int i = 1; i < n; ++i)
        {
            for (int j = 0; j < m; ++j)
            {
                if (j > 0)
                    result[j] += result[j-1];
                //else
                    //result[i] no change
            }
        }
        return result[m-1];
    }
};
