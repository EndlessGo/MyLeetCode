//153. Find Minimum in Rotated Sorted Array
class Solution {
public:
    int findMin(vector<int>& nums) {
        //O(logn) time, O(1) space
        if (nums.empty()) return -1;
        int l = 0, r = nums.size()-1;
        int mid = 0;
        while (l <= r)
        {
            if (nums[l] <= nums[r])
                return nums[l];                
            mid = l + ((r-l)>>1);
            if (nums[l] <= nums[mid])
                l = mid+1;
            else
                r = mid;
        }
        return -1;
    }
};
