//*154. Find Minimum in Rotated Sorted Array II
class Solution {
public:
    int findMin(vector<int>& nums) {
        //O(logn) time, O(1) space
        if (nums.empty()) return -1;
        int l = 0, r = nums.size()-1;
        int mid = 0;
        while (l < r)
        {
            /*if (nums[l] < nums[r])
                return nums[l];
            */
            mid = l + (r-l)/2;
            if (nums[mid] > nums[r])
                l = mid+1;
            else if (nums[mid] < nums[r])
                r = mid;        
            else
                r -= 1;
        }
        return nums[l];
    }        
};
