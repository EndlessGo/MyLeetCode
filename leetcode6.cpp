//6. ZigZag Conversion
class Solution {
public:
    string convert(string s, int numRows) {
        //O(n) time, O(1) space
        if (numRows == 1)
            return s;
        string result;
        for (int i = 0; i < numRows; ++i)
        {
            bool even = true;
            for (int j = i; j < s.length(); )
            {
                //cout<<i<<":"<<j<<endl;                
                result += s[j];
                if (numRows-1==i || 0==i)
                {
                    j += 2*(numRows-1);
                }
                else
                {
                    if (even)
                    {
                        j += 2*(numRows-i-1);
                    }
                    else
                    {
                        j += 2*i;
                    }
                    even = !even;
                }
            }
        }
        return result;
    }
};

class Solution {
public:
    string convert(string s, int numRows) {
        //O(n) time, O(n) space
        if (numRows <= 1)
            return s;
        vector<string> db(numRows, "");
        for (int i = 0, row = 0, step = 1; i < s.length(); ++i)
        {
            db[row] += s[i];
            if (row == 0)
                step = 1;
            else if (row == numRows-1)
                step = -1;
            row += step;
        }
        string result;
        for (auto str : db)
        {
            result += str;
        }
        return result;
    }
};
