//5. Longest Palindromic Substring
//1. 方法1：DP
class Solution {
public:
    string longestPalindrome(string s) {
	//time O(n^2), space O(n^2)
        int len = s.length();
        if (len < 2) return s;
        vector<vector<bool>> dp(len, vector<bool>(len,false));
        for (int i = 0; i < len; ++i)
        {
            dp[i][i] = true;
        }
        int start = 0, max_len = 1;
        for (int j = 1; j < len; ++j)
        {
            for (int i = 0; i < j; ++i)
            {
                if (s[i] == s[j])
                {
                    if (j-i < 3) dp[i][j] = true;
                    else dp[i][j] = dp[i+1][j-1];
                }
                else
                {
                    dp[i][j] = false;
                }
                if (dp[i][j] && j-i+1 > max_len)
                {
                    max_len = j-i+1;
                    start = i;
                }
            }
        }
        return s.substr(start, max_len);
    }
};

//方法2：中心扩散法
class Solution {

	//time O(n^2), space O(1)
private:

    string centerSpread(string& s, int left, int right) {
        // left = right 的时候，此时回文中心是一个空隙，向两边扩散得到的回文子串的长度是奇数
        // right = left + 1 的时候，此时回文中心是一个字符，向两边扩散得到的回文子串的长度是偶数
        int size = s.size();
        int i = left;
        int j = right;
        while (i >= 0 && j < size) {
            if (s[i] == s[j]) {
                i--;
                j++;
            } else {
                break;
            }
        }
        // 这里要小心，跳出 while 循环时，恰好满足 s.charAt(i) != s.charAt(j)，因此不能取 i，不能取 j
        return s.substr(i + 1, j - i - 1);
    }

public:


    string longestPalindrome(string s) {
        // 特判
        int size = s.size();
        if (size < 2) {
            return s;
        }

        int maxLen = 1;
        string res = s.substr(0, 1);

        // 中心位置枚举到 len - 2 即可
        for (int i = 0; i < size - 1; i++) {
            string oddStr = centerSpread(s, i, i);
            string evenStr = centerSpread(s, i, i + 1);
            string maxLenStr = oddStr.size() > evenStr.size() ? oddStr : evenStr;
            if (maxLenStr.length() > maxLen) {
                maxLen = maxLenStr.size();
                res = maxLenStr;
            }
        }
        return res;
    }
};

//3.Manacher 算法
class Solution {
	//time O(n^2), space O(n)
private:

    int centerSpread(string s, int center) {
        int len = s.size();
        int i = center - 1;
        int j = center + 1;
        int step = 0;
        while (i >= 0 && j < len && s[i] == s[j]) {
            i--;
            j++;
            step++;
        }
        return step;
    }

public:
    string longestPalindrome(string s) {
        // 特判
        int size = s.size();
        if (size < 2) {
            return s;
        }

        // 得到预处理字符串
        string str = "#";
        for (int i = 0; i < s.size(); ++i) {
            str += s[i];
            str += "#";
        }
        int sSize = 2 * size + 1;
        int maxLen = 1;

        int start = 0;
        for (int i = 0; i < sSize; i++) {
            int curLen = centerSpread(str, i);
            if (curLen > maxLen) {
                maxLen = curLen;
                start = (i - maxLen) / 2;
            }
        }
        return s.substr(start, maxLen);
    }
};

//4.Manacher 算法
//https://mp.weixin.qq.com/s?__biz=MzIzMTE1ODkyNQ==&mid=2649410225&idx=1&sn=ed045e8edc3c49a436a328e5f0f37a55&chksm=f0b60f53c7c18645b4c04a69ad314723cce94ed56994d6f963c2275a2db8d85f973f15f508e4&mpshare=1&scene=23&srcid=1001JCsBlpxgUWjgixasChNQ#rd
	//time O(n), space O(n)
class Solution {
public:
    string longestPalindrome(string s) {
        // 特判
        int size = s.size();
        if (size < 2) {
            return s;
        }

        // 得到预处理字符串
        string str = "#";
        for (int i = 0; i < s.size(); ++i) {
            str += s[i];
            str += "#";
        }
        // 新字符串的长度
        int strSize = 2 * size + 1;
        // 数组 p 记录了扫描过的回文子串的信息
        vector<int> p(strSize, 0);

        // 双指针，它们是一一对应的，须同时更新
        int maxRight = 0;
        int center = 0;

        // 当前遍历的中心最大扩散步数，其值等于原始字符串的最长回文子串的长度
        int maxLen = 1;
        // 原始字符串的最长回文子串的起始位置，与 maxLen 必须同时更新
        int start = 0;

        for (int i = 0; i < strSize; ++i) {
            if (i < maxRight) {
                int mirror = (2 * center) - i;
                // 这一行代码是 Manacher 算法的关键所在，要结合图形来理解
                p[i] = min(maxRight - i, p[mirror]);
            }

            // 下一次尝试扩散的左右起点，能扩散的步数直接加到 p[i] 中
            int left = i - (1 + p[i]);
            int right = i + (1 + p[i]);

            // left >= 0 && right < sLen 保证不越界
            // str.charAt(left) == str.charAt(right) 表示可以扩散 1 次
            while (left >= 0 && right < strSize && str[left] == str[right]) {
                p[i]++;
                left--;
                right++;

            }

            // 根据 maxRight 的定义，它是遍历过的 i 的 i + p[i] 的最大者
            // 如果 maxRight 的值越大，进入上面 i < maxRight 的判断的可能性就越大，这样就可以重复利用之前判断过的回文信息了
            if (i + p[i] > maxRight) {
                // maxRight 和 center 需要同时更新
                maxRight = i + p[i];
                center = i;
            }
            if (p[i] > maxLen) {
                // 记录最长回文子串的长度和相应它在原始字符串中的起点
                maxLen = p[i];
                start = (i - maxLen) / 2;
            }
        }
        return s.substr(start, maxLen);
    }
};

