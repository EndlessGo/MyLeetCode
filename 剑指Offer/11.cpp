//19点29分~20点44分
//*剑指 Offer 11. 旋转数组的最小数字
//*154. Find Minimum in Rotated Sorted Array II
class Solution {
public:
    int minArray(vector<int>& nums) {
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
