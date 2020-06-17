//268. Missing Number
class Solution {
public:
    int missingNumber(vector<int>& nums) {
        //we know total sum is n*(1+n)/2, so we iterate to compute missing array's sum, then minor
	//O(n) time, O(1) space
        int size = nums.size();
        int sum = 0;
        for(auto& num: nums)
        {
            sum += num;
        }
        return size*(1+size)/2 - sum;
    }
};

class Solution {
public:
    int missingNumber(vector<int>& nums) {
        //xor,  a^a = 0
        //[0 1...a...n] ^ [0 1...n] = a
        //O(n) time, O(1) space
        int result = 0;
        for(int i = 0; i < nums.size(); ++i)
        {
            result ^= i^nums[i];
        }
        return result^nums.size();//mention the last "n"
    }
};
