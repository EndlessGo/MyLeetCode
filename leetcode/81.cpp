//81. Search in Rotated Sorted Array II
class Solution {
public:
    bool search(vector<int>& nums, int target) {
        //O(logn) time, duplicates lead to O(n), O(1) space
        if (nums.empty()) return false;
        int l = 0, r = nums.size()-1;
        int mid = 0;
        while (l <= r)
        {           
            mid = l + ((r-l)>>1);
            if (target == nums[mid]) return true;
            if (nums[l] < nums[mid])
            {
                if (target >= nums[l] && target < nums[mid])
                    r = mid - 1;
                else
                    l = mid + 1;
            }
            else if (nums[l] > nums[mid])
            {
                if (target > nums[mid] && target <= nums[r])
                    l = mid + 1;
                else
                    r = mid - 1;
            }
            else//nums[l] == nums[mid]
                ++l;
        }
        return false;
    }
};
