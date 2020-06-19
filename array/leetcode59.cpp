//59. Spiral Matrix II
class Solution {
public:
    vector<vector<int>> generateMatrix(int n) {
        //2020年6月19日11:35:09 ---- 2020年6月19日11:42:36
	//same as leetcode 54. Spiral Matrix
        //time O(m*n), space O(1) no contain output
        vector<vector<int>> matrix(n, vector<int>(n,0));
        int num = 1, n_square = n*n;
        int left = 0, right = n-1;
        int up = 0, down = n-1;
        while (num <= n_square)
        {
            for (int i = left; i <= right && num <= n_square; ++i, ++num)
                matrix[up][i] = num;
            ++up;
            for (int i = up; i <= down && num <= n_square; ++i, ++num)
                matrix[i][right] = num;
            --right;
            for (int i = right; i >= left && num <= n_square; --i, ++num)
                matrix[down][i] = num;
            --down;
            for (int i = down; i >= up && num <= n_square; --i, ++num)
                matrix[i][left] = num;
            ++left;
        }
        return matrix;
    }
};
