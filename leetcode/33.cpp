//33. Search in Rotated Sorted Array
class Solution {
public:
    int search(vector<int>& nums, int target) {
	//O(n) time, O(1) space
        if (nums.empty()) return -1;
        int l = 0, r = nums.size()-1;
        int mid = 0;
        while (l <= r)
        {
            mid = l + (r-l)/2;
            if (target == nums[mid]) return mid;
            if (nums[l] <= nums[mid])
            {
                if (target < nums[mid] && target >= nums[l])
                    r = mid - 1;
                else
                    l = mid + 1;
            }
            else// nums[l] > nums[mid]
            {
                if (target > nums[mid] && target <= nums[r])
                    l = mid + 1;
                else
                    r = mid - 1;
            }
        }
        return -1;
    }
};
