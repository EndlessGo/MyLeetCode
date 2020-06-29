//剑指 Offer 13. 机器人的运动范围
//1. DFS
class Solution {
public:
    int movingCount(int m, int n, int k) {
        if (k < 0 || m <=0 || n <= 0) return 0;
	//O(mn) time, O(mn) space
        vector<vector<bool>> visited(m, vector<bool>(n,false));
        return DFS(0,0,m,n,k,visited);
    }
private:
    int DFS(int i, int j, int m, int n, int k, vector<vector<bool>>& visited)
    {
        //cout << i <<","<< j <<","<< m <<","<< n << endl;
        if (i < 0 || i >= m || j < 0 || j >= n || visited[i][j] || DigitSum(i) + DigitSum(j) > k)
            return 0;
        visited[i][j] = true;
        return 1 + DFS(i+1, j, m, n, k, visited)
                + DFS(i, j+1, m, n, k, visited)
                + DFS(i-1, j, m, n, k, visited)
                + DFS(i, j-1, m, n, k, visited);
    }
    int DigitSum(int x)
    {
        int result = 0;
        while (x)
        {
            result += (x%10);
            x /= 10;
        }
        return result;
    }
};

//2. BFS
class Solution {
public:
    struct Node
    {
        int x;
        int y;
    };
    int movingCount(int m, int n, int k) {
        if (k < 0 || m <=0 || n <= 0) return 0;
        //O(mn) time, O(mn) space
        vector<vector<bool>> visited(m, vector<bool>(n,false));
        queue<Node> que;
        que.push(Node{0,0});
        visited[0][0] = true;
        int count = 1;
        int dx[2] = {0,1};        
        int dy[2] = {1,0};
        while (!que.empty())
        {
            Node node = que.front();
            que.pop();
            for (int i = 0; i < 2; ++i)
            {
                int nx = node.x+dx[i];
                int ny = node.y+dy[i];
                if (nx >= m || ny >= n || visited[nx][ny] || DigitSum(nx) + DigitSum(ny) > k)
                    continue;
                que.push(Node{nx,ny});
                visited[nx][ny] = true;
                ++count;
            }
        }
        return count;
    }
private:
    int DigitSum(int x)
    {
        int result = 0;
        while (x)
        {
            result += (x%10);
            x /= 10;
        }
        return result;
    }
};
//3. DP
class Solution {
public:
    struct Node
    {
        int x;
        int y;
    };
    int movingCount(int m, int n, int k) {
        if (k < 0 || m <=0 || n <= 0) return 0;
        //O(mn) time, O(mn) space
        vector<vector<bool>> visited(m, vector<bool>(n,false));
        visited[0][0] = true;
        int count = 1;
        for (int i = 0; i < m; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                if ((i == 0 && j == 0) || DigitSum(i) + DigitSum(j) > k)
                    continue;
                if (i-1 >= 0) visited[i][j] = visited[i][j] || visited[i-1][j];
                if (j-1 >= 0) visited[i][j] = visited[i][j] || visited[i][j-1];
                if (visited[i][j])
                    ++count;
            }
        }
        return count;
    }
private:
    int DigitSum(int x)
    {
        int result = 0;
        while (x)
        {
            result += (x%10);
            x /= 10;
        }
        return result;
    }
};
