//885. Spiral Matrix III
class Solution {
public:
    vector<vector<int>> spiralMatrixIII(int R, int C, int r0, int c0) {
        //2020年6月19日13:37:48----2020年6月19日14:11:52
        //time O(R*C), space O(1) no cotain output
        //no need check valid
        /*if (r0 >= R || c0 >= C)
            return vector<vector<int>>();
        */
        int dr[] = {0, 1, 0, -1};
        int dc[] = {1, 0, -1, 0};
        int matrix_size = R*C;
        vector<vector<int>> matrix(matrix_size, vector<int>(2,0));
        int t = 0;
        matrix[t][0] = r0, matrix[t][1] = c0;
        ++t;
        if (R*C == 1)
            return matrix;
        int distance = 1;
        while (t < matrix_size)
        {
            for (int i = 0; i < 4; ++i) {  // i: direction index
                int dk = distance + (i / 2);  // number of steps in this direction
                for (int j = 0; j < dk; ++j) {  // for each step in this direction...
                    // step in the i-th direction
                    r0 += dr[i];
                    c0 += dc[i];
                    if (0 <= r0 && r0 < R && 0 <= c0 && c0 < C) {
                        matrix[t][0] = r0, matrix[t][1] = c0;
                        ++t;
                    }
                }
            }
            distance += 2;
        }        
        return matrix;
    }
};
