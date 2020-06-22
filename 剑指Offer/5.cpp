//剑指 Offer 05. 替换空格
class Solution {
public:
    string replaceSpace(string s) {
        //21点31分~21点40分
        if (s.empty())  return s;
        string result;
        result.resize(3*s.length());
        int size = -1;
        for(int i = 0; i < s.length(); ++i)
        {
            if (s[i] == ' ')
            {
                result[++size] = '%';
                result[++size] = '2';
                result[++size] = '0';
            }
            else
                result[++size] = s[i];
        }
        return result;
    }
};
