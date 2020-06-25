//153. Find Minimum in Rotated Sorted Array
class Solution {
public:
    int findMin(vector<int>& nums) {
        //[l...mid...r]
        //1. nums[l] <= nums[r], return nums[l]
        //2. nums[l] > nums[r]
        //2.1 nums[l] <= nums[mid], find in [mid+1...r]
        //2.2 nums[l] > nums[mid], find in [l...mid]
        //O(logn) time, O(1) space
        if (nums.empty()) return -1;
        int l = 0, r = nums.size()-1;
        int mid = 0;
        while (l <= r)
        {
            if (nums[l] <= nums[r])
                return nums[l];                
            mid = l + (r-l)/2;
            if (nums[l] <= nums[mid])
                l = mid+1;
            else
                r = mid;
        }
        return -1;
    }
};
