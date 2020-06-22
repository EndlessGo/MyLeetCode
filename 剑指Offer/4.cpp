//剑指 Offer 04. 二维数组中的查找
//leetcode 240. Search a 2D Matrix II
class Solution {
public:
    bool findNumberIn2DArray(vector<vector<int>>& matrix, int target) {
        //20点55分~21点26分
        //O(n+m) time, O(1) space
        if (matrix.empty())
            return false;
        int n = matrix.size();
        int m = matrix[0].size();
        int row = 0, col = m - 1;
        while (row < n && col >= 0)
        {
            if (matrix[row][col] == target)
                return true;
            else if (matrix[row][col] < target)
                ++row;
            else
                --col;
        }
        return false;
    }
};
