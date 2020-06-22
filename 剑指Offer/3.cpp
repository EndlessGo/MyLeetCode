//剑指 Offer 03. 数组中重复的数字
class Solution {
public:
    int findRepeatNumber(vector<int>& nums) {
        //2020年6月22日13:34:30~2020年6月22日13:41:34
        //time O(n), space O(n)
        unordered_set<int> record;
        for (auto& num: nums)
        {
            if (record.find(num) != record.end())
                return num;
            else
                record.insert(num);
        }
        return -1;
    }
};

class Solution {
public:
    int findRepeatNumber(vector<int>& nums) {
        //2020年6月22日13:34:30~2020年6月22日13:52:09
        //time O(n), space O(n)
        bool record[nums.size()];
        memset(record, false, nums.size());
        for (auto& num: nums)
        {
            if (record[num])
                return num;
            else
                record[num] = true;
        }
        return -1;
    }
};
