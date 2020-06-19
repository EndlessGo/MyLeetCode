//54. Spiral Matrix
//1: 不遍历到底：
//需要清晰掌握循环条件；<
//出循环后还有三种情况:一行多列，多行一列和一行一列。
class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        //1h50min, error
        //1h, two solution
        //time O(m*n), space O(1) no contain output
        if (matrix.empty())
            return vector<int>();
        if (matrix.size() == 1)
            return matrix[0];
        int left = 0, up = 0;
        int down = matrix.size() - 1;
        int right = matrix[0].size() -1;
        vector<int> result;
        while (left < right && up < down)
        {
            for (int i = left; i < right; ++i)
                result.push_back(matrix[up][i]);
            for (int i = up; i < down; ++i)
                result.push_back(matrix[i][right]);
            for (int i = right; i > left; --i)
                result.push_back(matrix[down][i]);                
            for (int i = down; i > up; --i)
                result.push_back(matrix[i][left]);
            ++left,++up;
            --right,--down;
        }
        //one row(contain one row one colum)
        if (up == down)
        {
            for (int i = left; i <= right; ++i)
                result.push_back(matrix[up][i]);            
        }
        else if (left == right)
        {
            for (int i = up; i <= down; ++i)
                result.push_back(matrix[i][right]);
        }
        return result;
    }
};

//2: 遍历到底
//循环条件清晰，转圈就完事了。
class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        //1h50min, error
        //1h, two solution
        //time O(m*n), space O(1) no contain output
        if (matrix.empty())
            return vector<int>();
        if (matrix.size() == 1)
            return matrix[0];
        int left = 0, up = 0;
        int down = matrix.size() - 1;
        int right = matrix[0].size() -1;
        vector<int> result;
        int element_num = matrix.size()*matrix[0].size();
        while (element_num >= 1)
        {
            for (int i = left; i <= right && element_num >= 1; ++i, --element_num)
                result.push_back(matrix[up][i]);
            ++up;
            for (int i = up; i <= down && element_num >= 1; ++i, --element_num)
                result.push_back(matrix[i][right]);
            --right;
            for (int i = right; i >= left && element_num >= 1; --i, --element_num)
                result.push_back(matrix[down][i]);                
            --down;
            for (int i = down; i >= up && element_num >= 1; --i, --element_num)
                result.push_back(matrix[i][left]);            
            ++left;
            //cout<<element_num<<endl;
        }
        return result;
    }
};
