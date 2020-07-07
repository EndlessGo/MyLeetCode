//剑指 Offer 29. 顺时针打印矩阵
//1.边界
class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        //O(mn) time, O(mn) space
        if (matrix.empty()) return vector<int>();
        if (matrix.size() == 1) return matrix[0];
        int left = 0, right = matrix[0].size()-1;
        int up = 0, down = matrix.size()-1;

        vector<int> result;
        int nums = matrix[0].size()*matrix.size();
        while (nums > 0)
        {
            for (int i = left; i <= right && nums > 0; ++i, --nums)
                result.push_back(matrix[up][i]);
            ++up;
            for (int i = up; i <= down && nums > 0; ++i, --nums)
                result.push_back(matrix[i][right]);
            --right;
            for (int i = right; i >= left && nums > 0; --i, --nums)
                result.push_back(matrix[down][i]);
            --down;
            for (int i = down; i >= up && nums > 0; --i, --nums)
                result.push_back(matrix[i][left]);
            ++left;
        }
        return result;
    }
};
//2.方向模拟
class Solution {
private:
    static constexpr int directions[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        //O(mn) time, O(mn) space
        if (matrix.size() == 0 || matrix[0].size() == 0) {
            return {};
        }
        
        int rows = matrix.size(), columns = matrix[0].size();
        vector<vector<bool>> visited(rows, vector<bool>(columns));
        int total = rows * columns;
        vector<int> order(total);

        int row = 0, column = 0;
        int directionIndex = 0;
        for (int i = 0; i < total; i++) {
            order[i] = matrix[row][column];
            visited[row][column] = true;
            int nextRow = row + directions[directionIndex][0], nextColumn = column + directions[directionIndex][1];
            if (nextRow < 0 || nextRow >= rows || nextColumn < 0 || nextColumn >= columns || visited[nextRow][nextColumn]) {
                directionIndex = (directionIndex + 1) % 4;
            }
            row = nextRow;
            column = nextColumn;
        }
        return order;
    }
};
