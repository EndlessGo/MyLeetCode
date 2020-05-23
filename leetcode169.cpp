//169. Majority Element
class Solution {
public:
    int majorityElement(vector<int>& nums) {
        //time O(n), space O(1)
        int major = 0, count = 0;
        for (auto& num: nums)
        {
            if(!count)
            {
                count = 1;
                major = num;
            }
            else
            {
                count += (num == major) ? 1 : -1;
            }
        }
        return major;
    }
};
