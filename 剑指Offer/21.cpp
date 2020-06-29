//剑指 Offer 21. 调整数组顺序使奇数位于偶数前面
class Solution {
public:
    vector<int> exchange(vector<int>& nums) {
        //O(n) time, O(1) space
        //[0..i] save odd, [i+1..end] save even
        int odd_end = -1;
        for (int i = 0; i < nums.size(); ++i)
        {
            if (nums[i] % 2)
                swap(nums[++odd_end], nums[i]);
        }
        return nums;
    }
};
