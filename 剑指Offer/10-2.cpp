//剑指 Offer 10- II. 青蛙跳台阶问题
//1.同10-I. 边界不同
class Solution {
public:
    Solution():p(1000000007) {}
    int numWays(int n) {
        //O(n) time, O(1) space
        if (n == 0) return 1;
        if (n == 1) return 1;
        int a = 1, b = 1, sum = 0;
        for (int i = 2; i <= n; ++i)
        {
            sum = (a+b)%p;
            a = b;
            b = sum;
        }
        return sum;
    }
private:
    int p;
};

//2.https://leetcode-cn.com/problems/qing-wa-tiao-tai-jie-wen-ti-lcof/solution/dong-tai-gui-hua-by-ml-zimingmeng/
const int p = 1000000007;
class Solution {
public:
    int numWays(int n) {
        //O(logn) time, O(1) space
        if (n == 0 || n == 1) return 1;
        long q[2][2] = { {1,1}, {1,0}};
        long res[2][2];
        PowMatrix(q,n,res);
        return res[0][0];
    }
    void PowMatrix(long a[2][2], int n, long res[2][2]) {
        long ret[2][2] = {{1, 0}, {0, 1}};
        while (n > 0) {
            if (n & 1) {
                MultiMatrix(ret, a);
            }
            n >>= 1;
            MultiMatrix(a, a);
        }
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 2; j++) {
                res[i][j] = ret[i][j];
            }
        }
        return;
    }    
    void MultiMatrix(long a[2][2], long b[2][2])
    {
        long c[2][2];
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 2; j++) {
                c[i][j] = ((a[i][0] * b[0][j])%p + (a[i][1] * b[1][j])%p)%p;
            }
        }
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 2; j++) {
                a[i][j] = c[i][j];
            }
        }        
        return;
    }
};
