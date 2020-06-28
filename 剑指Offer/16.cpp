//剑指 Offer 16. 数值的整数次方
//leetcode 50. Pow(x, n)
class Solution {
public:
    double myPow(double x, int n) {
        //13点54分~14点10分
        //x^n   = (x^2)^n/2  n=even
        //      = x(x^2)^(n-1)/2 n=odd
        //O(logn) time, O(1) space
        if (n == 0) return 1.0;
        if (n == 1) return x;
        long exp = n;
        if (n < 0) 
        {
            exp = -exp;
            x = 1/x;
        }
        double result = 1.0;
        while (exp)
        {
            if (exp%2)
            {
                result *= x;
            }
            x *= x;
            exp /= 2;
        }
        return result;
    }
};
