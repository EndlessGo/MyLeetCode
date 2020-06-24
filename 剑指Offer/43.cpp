//*剑指 Offer 43. 1～n整数中1出现的次数
//233. Number of Digit One
class Solution {
public:
    int countDigitOne(int n) {
        //23点16分~00点05分
        //O(logk) time, k 是 n的十进制位数，O(1) space
        if (n <= 0) return 0;
        long long digit = 1;
        int res = 0;
        int high = n/10, cur = n%10, low = 0;
        while (high || cur)
        {
            if (cur == 0)
                res += high*digit;
            else if (cur == 1)
                res += high*digit + low + 1;
            else
                res += (high+1)*digit;
            low += cur*digit;
            cur = high%10;
            high /= 10;
            digit *= 10;
        }
        return res;
    }
};
