//剑指 Offer 15. 二进制中1的个数
//191. Number of 1 Bits
class Solution {
public:
    int hammingWeight(uint32_t n) {
	//O(1) time, O(1) space
        int count = 0;
        while (n)
        {
            n &= (n-1);
            ++count;
        }
        return count;
    }
};
