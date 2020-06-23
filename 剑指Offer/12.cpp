//剑指 Offer 12. 矩阵中的路径
//1.DFS
class Solution {
public:
    bool exist(vector<vector<char>>& board, string word) {
        //2020-6-23 17:17:15~2020-6-23 18:05:23
	//time O(3^k*mn), space O(m*n)
        if (word.empty())
            return true;
        if (board.empty())
            return false;
        m = board.size(), n = board[0].size();
        visited = vector<vector<bool>>(m, vector<bool>(n,false));
        for (int i = 0; i < m; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                if (DFS(board, i, j, word, 0))
                    return true;
            }
        }
        return false;
    }
    bool DFS(vector<vector<char>>& board, int row, int col, string& word, int k) {
        if (k == word.length())
            return true;
        if (row < 0 || row >= m || col < 0 || col >= n || board[row][col] != word[k] || visited[row][col])
            return false;
        visited[row][col] = true;            
        bool result = DFS(board, row+1, col, word, k+1) || DFS(board, row, col+1, word, k+1) ||
                        DFS(board, row-1, col, word, k+1) || DFS(board, row, col-1, word, k+1);
        visited[row][col] = false;
        return result;
    }
private:
    vector<vector<bool>> visited;
    int m;
    int n;
};

//2.优化
class Solution {
public:
    bool exist(vector<vector<char>>& board, string word) {
	//time O(3^k*mn), space O(k)
        if (word.empty())
            return true;
        if (board.empty())
            return false;
        m = board.size(), n = board[0].size();
        for (int i = 0; i < m; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                if (DFS(board, i, j, word, 0))
                    return true;
            }
        }
        return false;
    }
    bool DFS(vector<vector<char>>& board, int row, int col, string& word, int k) {
        if (k == word.length())
            return true;
        if (row < 0 || row >= m || col < 0 || col >= n || board[row][col] != word[k])
            return false;
        char temp = board[row][col];
        board[row][col] = '/';
        bool result = DFS(board, row+1, col, word, k+1) || DFS(board, row, col+1, word, k+1) ||
                        DFS(board, row-1, col, word, k+1) || DFS(board, row, col-1, word, k+1);
        board[row][col] = temp;
        return result;
    }
private:
    int m;
    int n;
};
