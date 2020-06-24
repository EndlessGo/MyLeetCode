//面试题 01.01. 判定字符是否唯一
class Solution {
public:
    bool isUnique(string astr) {
        //22点46分~22点58分
        //1.unordered_set, ohter data structure...no
        //2.force, two for, O(n^2)...no
        //3.bit operation
        //O(n) time, O(1) space
        if (astr.empty()) return true;
        int mask = 0;
        for (int i = 0; i < astr.length(); ++i)
        {
            if (mask & (1<<(astr[i]-'a')))
                return false;
            else
                mask |= 1<<(astr[i]-'a');
        }
        return true;
    }
};
