//剑指 Offer 14- II. 剪绳子 II
//1.快速幂求余
class Solution {
public:
    int cuttingRope(int n) {
        if(n <= 3) return n-1;
        int p = 1000000007;
        //快速幂求余O(logn) time, O(1) space。如果时循环求余法就是O(n) time。 n是幂值
        long rem = 1, x = 3;
        for (int a = n/3-1; a > 0; a/=2)
        {
            if (a%2) rem = (rem*x)%p;
            x = (x*x)%p;            
        }
        int b = n % 3 ;
        if (b == 0) return rem*3%p;
        if (b == 1) return rem*4%p;
        else//b == 2) 
            return rem*6%p;
    }
};

//2.循环求余法
class Solution {
public:
    int cuttingRope(int n) {
        if(n <= 3) return n-1;
        long rs = 1;
        int p = 1000000007;
        while (n > 4) {
            //3最优
            rs *= 3;
            rs %= p;
            n -= 3;
        }
        return (rs * n) % p;
    }
};
