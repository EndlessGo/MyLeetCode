[TOC]

# Top Interview Questions

## 1. Two Sum

Easy

Given an array of integers, return **indices** of the two numbers such that they add up to a specific target.

You may assume that each input would have **exactly** one solution, and you may not use the *same* element twice.

**Example:**

```
Given nums = [2, 7, 11, 15], target = 9,

Because nums[0] + nums[1] = 2 + 7 = 9,
return [0, 1].
```

**Solution:**

```c++
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        //time O(n), space O(n)
        unordered_map<int,int> valIndexMap;
        int size = nums.size();
        auto end = valIndexMap.end();
        vector<int> res;
        for (int i = 0; i < size; ++i)
        {
            if (valIndexMap.find(target-nums[i]) != end)
            {
                res.push_back(valIndexMap[target-nums[i]]);
                res.push_back(i);
                break;
            }
            valIndexMap[nums[i]] = i;
        }
        return res;
    }
};
```



## 2. Add Two Numbers

Medium

You are given two **non-empty** linked lists representing two non-negative integers. The digits are stored in **reverse order** and each of their nodes contain a single digit. Add the two numbers and return it as a linked list.

You may assume the two numbers do not contain any leading zero, except the number 0 itself.

**Example:**

```
Input: (2 -> 4 -> 3) + (5 -> 6 -> 4)
Output: 7 -> 0 -> 8
Explanation: 342 + 465 = 807.
```

**Solution:**

```c++
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode* h1 = l1, *l1Tail = NULL;
        int carry = 0;
        while(l1 && l2)
        {
            int sum = l1->val + l2->val;
            l1->val = (carry +  sum) % 10;
            carry = (carry + sum ) / 10;
            if(l1->next == NULL)
            {
                l1Tail = l1;
            }
            l1 = l1->next;
            l2 = l2->next;
        }
        if(l2)
        {
            l1Tail->next = l2;
            l1 = l2;
        }
        while (l1)
        {
            int sum = l1->val + carry;
            l1->val = sum % 10;
            carry = sum / 10;
            if(l1->next == NULL)
            {
                l1Tail = l1;
            }            
            l1 = l1->next;
        }
        if (carry)
        {
            ListNode *tail = new ListNode(carry);
            l1Tail->next = tail;
        }
        return h1;
    }
};
```

**Improve:**

```c++
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode* dummy = new ListNode(0);
        ListNode* cur = dummy;
        int carry = 0;
        while(l1 || l2)
        {
            int sum = (l1?l1->val:0) + (l2?l2->val:0) + carry;
            carry = sum / 10;
            cur->next = new ListNode(sum % 10);
            if (l1) l1 = l1->next;
            if (l2) l2 = l2->next;
            cur = cur->next;
        }
        if (carry)
        {
            cur->next = new ListNode(carry);
        }
        return dummy->next;
    }
};
```



## 7. Reverse Integer

Easy

Given a 32-bit signed integer, reverse digits of an integer.

**Example 1:**

```
Input: 123
Output: 321
```

**Example 2:**

```
Input: -123
Output: -321
```

**Example 3:**

```
Input: 120
Output: 21
```

**Note:**
Assume we are dealing with an environment which could only store integers within the 32-bit signed integer range: [−231, 231 − 1]. For the purpose of this problem, assume that your function returns 0 when the reversed integer overflows.

**Solution:**

```c++
class Solution {
public:
    int reverse(int x) {
        //time O(n), space O(1)
        long a = 0 ;
        while(x)
        {
            a = 10*a + x%10;
            x /= 10;
        }
        return (a>INT_MAX||a<INT_MIN) ?0:a;
    }
};

class Solution {
public:
    int reverse(int x) {
        //time O(n), space O(n)
        char sign = x > 0? 1: -1;
        string str = to_string(x);
        //cout<<str<<endl;
        auto begin = str.begin();
        if(sign == -1)
            begin += 1;        
        std::reverse(begin, str.end());
        //cout<<str<<endl;
        long res = stoll(str);
        if(res > INT_MAX or res < INT_MIN)
            res = 0;
        return (int)res;
    }
};
```



## 8. String to Integer (atoi)

Medium

Implement `atoi` which converts a string to an integer.

The function first discards as many whitespace characters as necessary until the first non-whitespace character is found. Then, starting from this character, takes an optional initial plus or minus sign followed by as many numerical digits as possible, and interprets them as a numerical value.

The string can contain additional characters after those that form the integral number, which are ignored and have no effect on the behavior of this function.

If the first sequence of non-whitespace characters in str is not a valid integral number, or if no such sequence exists because either str is empty or it contains only whitespace characters, no conversion is performed.

If no valid conversion could be performed, a zero value is returned.

**Note:**

- Only the space character `' '` is considered as whitespace character.
- Assume we are dealing with an environment which could only store integers within the 32-bit signed integer range: [−2^31,  2^31 − 1]. If the numerical value is out of the range of representable values, INT_MAX (2^31 − 1) or INT_MIN (−2^31) is returned.

**Example 1:**

```
Input: "42"
Output: 42
```

**Example 2:**

```
Input: "   -42"
Output: -42
Explanation: The first non-whitespace character is '-', which is the minus sign.
             Then take as many numerical digits as possible, which gets 42.
```

**Example 3:**

```
Input: "4193 with words"
Output: 4193
Explanation: Conversion stops at digit '3' as the next character is not a numerical digit.
```

**Example 4:**

```
Input: "words and 987"
Output: 0
Explanation: The first non-whitespace character is 'w', which is not a numerical 
             digit or a +/- sign. Therefore no valid conversion could be performed.
```

**Example 5:**

```
Input: "-91283472332"
Output: -2147483648
Explanation: The number "-91283472332" is out of the range of a 32-bit signed integer.
             Thefore INT_MIN (−231) is returned.
```

**Solution:**

```c++
class Solution {
public:
    int myAtoi(string str) {
        long long res = 0;
        int size = str.size(), i = 0, symbol = 1;
        //discards witespace first
        while(i < size)
        {
            if (str[i] == ' ')
                ++i;
            else if(str[i] >= '0' && str[i] <= '9')
                break;
            else if (str[i] == '+' || str[i] == '-')
            {
                if (str[i] == '-')                    
                    symbol = -1;
                ++i;
                break;
            }
            else
                return 0;
        }
        //atoi, discards when not numerical digit
        while(i < size)
        {
            if(str[i] >= '0' && str[i] <= '9')
            {
                res = 10 * res + (str[i]-'0');                
                ++i;
                //cout<<res<<endl;
                if (res * symbol >= INT_MAX) return INT_MAX;
                if (res * symbol <= INT_MIN) return INT_MIN;
            }                
            else
                break;
        }
        res *= symbol;
        //cout<<res<<endl;
        return (int)res;
    }
};
```



## 13. Roman to Integer

Easy

Roman numerals are represented by seven different symbols: `I`, `V`, `X`, `L`, `C`, `D` and `M`.

```
Symbol       Value
I             1
V             5
X             10
L             50
C             100
D             500
M             1000
```

For example, two is written as `II` in Roman numeral, just two one's added together. Twelve is written as, `XII`, which is simply `X` + `II`. The number twenty seven is written as `XXVII`, which is `XX` + `V` + `II`.

Roman numerals are usually written largest to smallest from left to right. However, the numeral for four is not `IIII`. Instead, the number four is written as `IV`. Because the one is before the five we subtract it making four. The same principle applies to the number nine, which is written as `IX`. There are six instances where subtraction is used:

- `I` can be placed before `V` (5) and `X` (10) to make 4 and 9. 
- `X` can be placed before `L` (50) and `C` (100) to make 40 and 90. 
- `C` can be placed before `D` (500) and `M` (1000) to make 400 and 900.

Given a roman numeral, convert it to an integer. Input is guaranteed to be within the range from 1 to 3999.

**Example 1:**

```
Input: "III"
Output: 3
```

**Example 2:**

```
Input: "IV"
Output: 4
```

**Example 3:**

```
Input: "IX"
Output: 9
```

**Example 4:**

```
Input: "LVIII"
Output: 58
Explanation: L = 50, V= 5, III = 3.
```

**Example 5:**

```
Input: "MCMXCIV"
Output: 1994
Explanation: M = 1000, CM = 900, XC = 90 and IV = 4.
```

```c++
class Solution {
public:
    int romanToInt(string s) {
        //time O(n), space O(1)
        int res = 0;
        for(int i = 0; i < s.size(); ++i)
        {
            string tmp;
            tmp.push_back(s[i]);
            int val = record[tmp];
            if(s[i] == 'I' || s[i] == 'X' || s[i] == 'C')
            {                
                if(i+1 < s.size())
                {
                    tmp.push_back(s[i+1]);
                    if(record.find(tmp) != record.end())
                    {
                        ++i;
                        val = record[tmp];
                    }
                }
            }
            res += val;
        }
        return res;
    }
private:
    unordered_map<string, int> record = {
        {"I", 1},
        {"V", 5},
        {"X", 10},
        {"L", 50},
        {"C", 100},
        {"D", 500},
        {"M", 1000},
        {"IV", 4}, {"IX", 9},
        {"XL", 40}, {"XC", 90},
        {"CD", 400}, {"CM", 900},
    };
};
```



## 14. Longest Common Prefix

Easy

Write a function to find the longest common prefix string amongst an array of strings.

If there is no common prefix, return an empty string `""`.

**Example 1:**

```
Input: ["flower","flow","flight"]
Output: "fl"
```

**Example 2:**

```
Input: ["dog","racecar","car"]
Output: ""
Explanation: There is no common prefix among the input strings.
```

**Note:**

All given inputs are in lowercase letters `a-z`.

**Solution:**

```c++
class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {
        //time O(m*n), space O(1)
        if(strs.empty())
            return "";
        int count = 0;
        while(count < strs[0].size())
        {
            char tmp = strs[0][count];
            for(int j = 1; j < strs.size(); ++j)
            {
                if(strs[j][count] != tmp)
                    return strs[0].substr(0,count);
            }
            ++count;
        }
        return strs[0];
    }
};

class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {
        if (strs.empty())   return "";
        if (strs.size() == 1) return strs[0];
        string res;
        int prefix = 0;
        while(true)
        {
            int size = strs.size();
            for (int i = 1; i < size; ++i)
            {
                if ( prefix >= strs[i-1].length() || prefix >= strs[i].length() || strs[i-1][prefix] != strs[i][prefix])
                {
                    return res;
                }
            }
            res += strs[0][prefix];
            ++prefix;
        }
    }
};
```



## 17. Letter Combinations of a Phone Number

Medium

Given a string containing digits from `2-9` inclusive, return all possible letter combinations that the number could represent.

A mapping of digit to letters (just like on the telephone buttons) is given below. Note that 1 does not map to any letters.

![img](http://upload.wikimedia.org/wikipedia/commons/thumb/7/73/Telephone-keypad2.svg/200px-Telephone-keypad2.svg.png)

**Example:**

```
Input: "23"
Output: ["ad", "ae", "af", "bd", "be", "bf", "cd", "ce", "cf"].
```

**Note:**

Although the above answer is in lexicographical order, your answer could be in any order you want.

**Solution 1:** push_back() and pop_back()

```c++
class Solution {
public:
    vector<string> letterCombinations(string digits) {        
        result.clear();
        if(digits.empty())  return result;
        string s = "";
        findCombination(digits, 0, s);
        return result;
    }
    //temp中保存了从digits[0...index-1]翻译得到的一个字符串字母
    //寻找和digits[index]匹配的字母，并翻译得到digits[0...index]
    void findCombination(string& digits, int index, string& temp)
    {
        //cout<<"index="<<index<<endl;
        if(index == digits.size())
        {
            result.push_back(temp);
            return;
        }
        string letters = record[digits[index]-'0'];
        //cout<<letters<<endl;
        int size = letters.size();
        for(int i = 0; i < size; ++i)
        {
            //cout<<"i="<<i<<endl;
            temp.push_back(letters[i]);
            findCombination(digits, index+1, temp);
            temp.pop_back();
        }
        return;
    }
private:
    vector<string> record
    {
        "",//0
        "",//1
        "abc",
        "def",
        "ghi",
        "jkl",
        "mno",
        "pqrs",
        "tuv",
        "wxyz",//9
    };
    vector<string> result;
};
```

**Solution 2:** const string& temp, a little bit more memory because temp and temp+letter[i] are two different strings.

```c++
    vector<string> letterCombinations(string digits) {        
        result.clear();
        if(digits.empty())  return result;
        //string s = "";
        findCombination(digits, 0, "");
        return result;
    }
    //temp中保存了从digits[0...index-1]翻译得到的一个字符串字母
    //寻找和digits[index]匹配的字母，并翻译得到digits[0...index]
    void findCombination(string& digits, int index, const string& temp)
    {
        //cout<<"index="<<index<<endl;
        if(index == digits.size())
        {
            result.push_back(temp);
            return;
        }
        string letters = record[digits[index]-'0'];
        //cout<<letters<<endl;
        int size = letters.size();
        for(int i = 0; i < size; ++i)
        {
            //cout<<"i="<<i<<endl;
            //temp.push_back(letters[i]);
            findCombination(digits, index+1, temp + letters[i]);
            //temp.pop_back();
        }
        return;
    }
```



## 20. Valid Parentheses

Easy

Given a string containing just the characters `'('`, `')'`, `'{'`, `'}'`, `'['` and `']'`, determine if the input string is valid.

An input string is valid if:

1. Open brackets must be closed by the same type of brackets.
2. Open brackets must be closed in the correct order.

Note that an empty string is also considered valid.

**Example 1:**

```
Input: "()"
Output: true
```

**Example 2:**

```
Input: "()[]{}"
Output: true
```

**Example 3:**

```
Input: "(]"
Output: false
```

**Example 4:**

```
Input: "([)]"
Output: false
```

**Example 5:**

```
Input: "{[]}"
Output: true
```

**Solution:**

```c++
class Solution {
public:
    bool isValid(string s) {
        stack<char> res;
        int size = s.size();
        for(int i = 0; i < size; ++i)
        {
            if(s[i] == ')' || s[i] == ']' || s[i] == '}')
            {
                if (res.empty())
                    return false;
                char top;
                if(s[i] == ')')
                    top = '(';
                else if(s[i] == '}')
                    top = '{';
                else// if(s[i] == ']')
                    top = '[';
                if(res.top() != top)
                    return false;
                res.pop();
            }       
            else
                res.push(s[i]);
        }
        return res.empty();
    }
};
```



## 21. Merge Two Sorted Lists

Easy

Merge two sorted linked lists and return it as a new list. The new list should be made by splicing together the nodes of the first two lists.

**Example:**

```
Input: 1->2->4, 1->3->4
Output: 1->1->2->3->4->4
```

**Solution:**

```c++
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        //time O(n), space O(1)
        ListNode dummyHead(0);
        ListNode* cur = &dummyHead;
        while(l1 && l2)
        {
            if(l1->val <= l2->val)
            {
                cur->next = l1;
                l1 = l1->next;
            }
            else
            {
                cur->next = l2;
                l2 = l2->next;                    
            }
            cur = cur->next;
        }
        cur->next = l1? l1:l2;
        return dummyHead.next;
    }
};
```



## 22. Generate Parentheses

Medium

Given *n* pairs of parentheses, write a function to generate all combinations of well-formed parentheses.

For example, given *n* = 3, a solution set is:

```
[
  "((()))",
  "(()())",
  "(())()",
  "()(())",
  "()()()"
]
```

**Solution:** backtrack

```c++
class Solution {
public:
    vector<string> generateParenthesis(int n) {
        vector<string> res;
        backtrack(res, "", n, 0);
        return res;
    }
private:
    void backtrack(vector<string>& res, string str, int n, int m)
    {
        //use two integers to count the remaining left parenthesis (n) and the right parenthesis (m) to be added
        if (!n && !m)
        {
            res.push_back(str);
            return;
        }
        if (m > 0)
            backtrack(res, str+")", n, m-1);
        if (n > 0)
            backtrack(res, str+"(", n-1, m+1);
        return;
    }
};
```



## 26. Remove Duplicates from Sorted Array

Easy

Given a sorted array *nums*, remove the duplicates [**in-place**](https://en.wikipedia.org/wiki/In-place_algorithm) such that each element appear only *once* and return the new length.

Do not allocate extra space for another array, you must do this by **modifying the input array [in-place](https://en.wikipedia.org/wiki/In-place_algorithm)** with O(1) extra memory.

**Example 1:**

```
Given nums = [1,1,2],

Your function should return length = 2, with the first two elements of nums being 1 and 2 respectively.

It doesn't matter what you leave beyond the returned length.
```

**Example 2:**

```
Given nums = [0,0,1,1,1,2,2,3,3,4],

Your function should return length = 5, with the first five elements of nums being modified to 0, 1, 2, 3, and 4 respectively.

It doesn't matter what values are set beyond the returned length.
```

**Solution**

```c++
class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        //time O(n), space O(1)
        if(nums.empty()) return 0;
        int count = 1, size = nums.size();//nums[0...count) store appear once element
        for(int i = 1; i < size; ++i)
        {
            if(nums[i] != nums[i-1])
            {
                //if(i != count)
                    nums[count++] = nums[i];
                //else
                    //++count;
            }
        }
        return count;
    }
};
```



## 28. Implement strStr()

Easy

Implement [strStr()](http://www.cplusplus.com/reference/cstring/strstr/).

Return the index of the first occurrence of needle in haystack, or **-1** if needle is not part of haystack.

**Example 1:**

```
Input: haystack = "hello", needle = "ll"
Output: 2
```

**Example 2:**

```
Input: haystack = "aaaaa", needle = "bba"
Output: -1
```

**Clarification:**

What should we return when `needle` is an empty string? This is a great question to ask during an interview.

For the purpose of this problem, we will return 0 when `needle` is an empty string. This is consistent to C's [strstr()](http://www.cplusplus.com/reference/cstring/strstr/) and Java's [indexOf()](https://docs.oracle.com/javase/7/docs/api/java/lang/String.html#indexOf(java.lang.String)).

**Solution:**

```c++
class Solution {
public:
    int strStr(string haystack, string needle) {
        //time O(n*m), space O(1)
        if (needle.empty()) return 0;
        int hsize = haystack.size(), nsize = needle.size();
        for(int i = 0; i <= hsize-nsize; ++i)
        {
            int j = 0;
            for(; j < nsize; ++j)
            {
                if (haystack[i+j] != needle[j])
                    break;
            }
            if (j == nsize)
                return i;
        }
        return -1;
    }
};
```

**Improved:** KMP

```c++
class Solution {
public:
    int strStr(string haystack, string needle) {
        //time O(n+m), space O(1)
        if (needle.empty()) return 0;
        vector<int> next = kmpProcess(needle);
        int m = haystack.size(), n = needle.size();
        for(int i = 0, j = 0; i < m;)
        {
            while(j < n && haystack[i] == needle[j])
            {
                ++i;++j;
            }
            if(j == n)
                return i-j;            
            //cout<<"j="<<j<<endl;
            j ? j = next[j-1] : ++i;
            //cout<<"i="<<i<<"j="<<j<<endl;
        }
        return -1;
    }
private:
    vector<int> kmpProcess(string needle) {
        int n = needle.size();
        vector<int> next(n, 0);//next[i] means string needle match [0,i], when i+1 dismatch, the index next to be compared
        for(int i = 0, j = 1; j < n;)
        {
            if(needle[j] == needle[i])
                next[j++] = ++i;
            else if(i)//if(needle[j] == needle[i] && i != 0)
            {
                i = next[i-1];
            }
            else//if(i == 0)
                next[j++] = 0;
        }
        return next;
    }
};
```



## 38. Count and Say

Easy

The count-and-say sequence is the sequence of integers with the first five terms as following:

```
1.     1
2.     11
3.     21
4.     1211
5.     111221
```

`1` is read off as `"one 1"` or `11`.
`11` is read off as `"two 1s"` or `21`.
`21` is read off as `"one 2`, then `one 1"` or `1211`.

Given an integer *n* where 1 ≤ *n* ≤ 30, generate the *n*th term of the count-and-say sequence.

Note: Each term of the sequence of integers will be represented as a string.

 

**Example 1:**

```
Input: 1
Output: "1"
```

**Example 2:**

```
Input: 4
Output: "1211"
```

解释：

Careercup has a same problem, I think its description is better:
http://www.careercup.com/question?id=4425679

"Count and Say problem" Write a code to do following:

n String to print
0 1
1 1 1
2 2 1
3 1 2 1 1
...
Base case: n = 0 print "1"
for n = 1, look at previous string and write number of times a digit is seen and the digit itself. In this case,

digit 1 is seen 1 time in a row... so print "1 1"

for n = 2, digit 1 is seen two times in a row, so print "2 1"

for n = 3, digit 2 is seen 1 time and then digit 1 is seen 1 so print "1 2 1 1"

for n = 4 you will print "1 1 1 2 2 1"

Consider the numbers as integers for simplicity. e.g. if previous string is "10 1" then the next will be "1 10 1 1" and the next one will be "1 1 1 10 2 1"

**Solution**

```c++
class Solution {
public:
    string countAndSay(int n) {
        if(1 <= n && n <= 5)
            return init[n-1];
        string res = init[init.size()-1];
        for(int i = 6; i <= n; ++i)
        {
            string cur = "";
            for(int j = 0; j < res.size(); ++j)
            {
                int count = 1;
                while(j+1 < res.size() && res[j] == res[j+1])
                {
                    ++count;
                    ++j;
                }
                cur += to_string(count) + res[j];
            }
            res = cur;
        }
        return res;
    }
private:
    vector<string> init = {"1", "11", "21", "1211", "111221"};
};
```



## 46. Permutations

Medium

Given a collection of **distinct** integers, return all possible permutations.

**Example:**

```
Input: [1,2,3]
Output:
[
  [1,2,3],
  [1,3,2],
  [2,1,3],
  [2,3,1],
  [3,1,2],
  [3,2,1]
]
```

**Solution**

```c++
class Solution {
public:
    vector<vector<int>> permute(vector<int>& nums) {        
        vector<vector<int>> res;
        if (nums.empty()) return res;
        permute(res, nums, 0);       
        return res;
    }
private:
    void permute(vector<vector<int>> &res, vector<int>& nums, int begin)
    {        
        int size = nums.size();
        if(begin == size)
        {
            res.push_back(nums);
            return;
        }
        for(int i = begin; i < size; ++i)
        {
            swap(nums[begin], nums[i]);
            permute(res, nums, begin+1);
            swap(nums[begin], nums[i]);
        }                
        return;
    }
};
```



## 48. Rotate Image

Medium

You are given an *n* x *n* 2D matrix representing an image.

Rotate the image by 90 degrees (clockwise).

**Note:**

You have to rotate the image [**in-place**](https://en.wikipedia.org/wiki/In-place_algorithm), which means you have to modify the input 2D matrix directly. **DO NOT** allocate another 2D matrix and do the rotation.

**Example 1:**

```
Given input matrix = 
[
  [1,2,3],
  [4,5,6],
  [7,8,9]
],

rotate the input matrix in-place such that it becomes:
[
  [7,4,1],
  [8,5,2],
  [9,6,3]
]
```

**Example 2:**

```
Given input matrix =
[
  [ 5, 1, 9,11],
  [ 2, 4, 8,10],
  [13, 3, 6, 7],
  [15,14,12,16]
], 

rotate the input matrix in-place such that it becomes:
[
  [15,13, 2, 5],
  [14, 3, 4, 1],
  [12, 6, 8, 9],
  [16, 7,10,11]
]
```

```c++
class Solution {
public:
    void rotate(vector<vector<int>>& matrix) {
        if (matrix.empty()) return;
        int n = matrix.size();
        for (int i = 0; i < n / 2; ++i)
        {
            for (int j = i; j < n - 1 - i; ++j)
            {
                int save = matrix[i][j];
                matrix[i][j] = matrix[n-1-j][i];
                matrix[n-1-j][i] = matrix[n-1-i][n-1-j];
                matrix[n-1-i][n-1-j] = matrix[j][n-1-i];
                matrix[j][n-1-i] = save;
            }
        }
        return;
    }
};
```



## 53. Maximum Subarray

Easy

Given an integer array `nums`, find the contiguous subarray (containing at least one number) which has the largest sum and return its sum.

**Example:**

```
Input: [-2,1,-3,4,-1,2,1,-5,4],
Output: 6
Explanation: [4,-1,2,1] has the largest sum = 6.
```

**Follow up:**

If you have figured out the O(*n*) solution, try coding another solution using the divide and conquer approach, which is more subtle.

**Solution1:** iterative

```c++
class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        //time O(n), space O(1)
        //nums.empty() always false
        int max_sum = INT_MIN, cur_sum = 0;
        for (auto num : nums)
        {
            if (cur_sum < 0)
                cur_sum = max(cur_sum, num);
            else
                cur_sum += num;
            max_sum = max(cur_sum, max_sum);
        }
        return max_sum;
    }
};
```

**Solution2:** dp

```c++
class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        //time O(n), space O(n)
        //nums.empty() always false
        int size = nums.size(), res = INT_MIN;
        //dp[i] means the maximum subarray ending with nums[i];
        vector<int> dp(size, INT_MIN);
        dp[0] = nums[0];
        res = dp[0];
        for (int i = 1; i < size; ++i)
        {
            dp[i] = max(dp[i-1]+nums[i], nums[i]);//bug if { INT_MIN, -1 }
            res = max(res, dp[i]);
        }
        return res;
    }
};
class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        //time O(n), space O(n)
        //nums.empty() always false
        int size = nums.size(), res = INT_MIN;
        //dp[i] means the maximum subarray ending with nums[i];
        vector<int> dp(size, INT_MIN);
        dp[0] = nums[0];
        res = dp[0];
        for (int i = 1; i < size; ++i)
        {
            dp[i] = dp[i-1] >= 0 ? dp[i-1]+nums[i] : max(dp[i-1], nums[i]);
            res = max(res, dp[i]);
        }
        return res;
    }
};
```

**Solution3**: divide and conquer

```c++
class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        //time O(nlogn), space O(1)
        return findMaxInRange(nums, 0, nums.size()-1);
    }
private:
    int findMaxInRange(vector<int>& nums, int begin, int end)
    {
        if(begin == end) return nums[begin];
        if(begin > end) return INT_MIN;
        int mid = begin+(end-begin)/2;
        int leftMax = findMaxInRange(nums, begin, mid-1);
        int rightMax = findMaxInRange(nums, mid+1, end);
        int midLMax = 0, midRMax = 0;
        for(int i = mid - 1, sum = 0; i >= begin; --i)
        {
            sum += nums[i];
            if(midLMax < sum)
                midLMax = sum;
        }
        for(int i = mid + 1, sum = 0; i <= end; ++i)
        {
            sum += nums[i];
            if(midRMax < sum)
                midRMax = sum;
        }
        return max(max(leftMax, rightMax), midLMax+midRMax+nums[mid]);
    }
};
```



## 55. Jump Game

Medium

Given an array of non-negative integers, you are initially positioned at the first index of the array.

Each element in the array represents your maximum jump length at that position.

Determine if you are able to reach the last index.

**Example 1:**

```
Input: [2,3,1,1,4]
Output: true
Explanation: Jump 1 step from index 0 to 1, then 3 steps to the last index.
```

**Example 2:**

```
Input: [3,2,1,0,4]
Output: false
Explanation: You will always arrive at index 3 no matter what. Its maximum
             jump length is 0, which makes it impossible to reach the last index.
```

**Solution:**

```c++
class Solution {
public:
    bool canJump(vector<int>& nums) {
        int last = nums.size()-1;
        for (int i = last; i >= 0; --i)
        {
            if (i+nums[i] >= last)
                last = i;        
        }
        return last == 0;
    }
};
```



## 66. Plus One

Easy

Given a **non-empty** array of digits representing a non-negative integer, plus one to the integer.

The digits are stored such that the most significant digit is at the head of the list, and each element in the array contain a single digit.

You may assume the integer does not contain any leading zero, except the number 0 itself.

**Example 1:**

```
Input: [1,2,3]
Output: [1,2,4]
Explanation: The array represents the integer 123.
```

**Example 2:**

```
Input: [4,3,2,1]
Output: [4,3,2,2]
Explanation: The array represents the integer 4321.
```

**Solution**

```c++
class Solution {
public:
    vector<int> plusOne(vector<int>& digits) {
        int carry = 1;
        for (int i = digits.size() - 1; i >= 0; --i)
        {
            int sum = digits[i] + carry;
            digits[i] = sum % 10;
            carry = sum / 10;
        }
        if (carry)
            digits.insert(digits.begin(), carry);
        return digits;
    }
};
```



## 69. Sqrt(x)

Easy

Implement `int sqrt(int x)`.

Compute and return the square root of *x*, where *x* is guaranteed to be a non-negative integer.

Since the return type is an integer, the decimal digits are truncated and only the integer part of the result is returned.

**Example 1:**

```
Input: 4
Output: 2
```

**Example 2:**

```
Input: 8
Output: 2
Explanation: The square root of 8 is 2.82842..., and since 
             the decimal part is truncated, 2 is returned.
```

Hide Hint 1:

 Try exploring all integers. (Credits: @annujoshi) 

Hide Hint 2:

 Use the sorted property of integers to reduced the search space. (Credits: @annujoshi) 

**Solution:**

```c++
class Solution {
public:
    int mySqrt(int x) {
        //O(n) time complexity
        if (!x) return 0;
        int i = 1;
        for (; i <= x/2; ++i)
        {
            if (i <= x/i && (i+1) > x/(i+1))
                break;
        }
        return i;
    }
};
```

**Improve:**

```c++
class Solution {
public:
    int mySqrt(int x) {
    	//O(logn) time complexity
        if (!x) return 0;
        int left = 1, right = x/2;
        while (true) 
        {
            int mid = left + (right-left)/2;
            if (mid > x/mid)
            {
                right = mid - 1;
            }
            else //if(mid <= x/mid)
            {
                if (mid+1 > x/(mid + 1))
                    return mid;
                left = mid + 1;
            }
        }
    }
};
```



## 70. Climbing Stairs

Easy

You are climbing a stair case. It takes *n* steps to reach to the top.

Each time you can either climb 1 or 2 steps. In how many distinct ways can you climb to the top?

**Note:** Given *n* will be a positive integer.

**Example 1:**

```
Input: 2
Output: 2
Explanation: There are two ways to climb to the top.
1. 1 step + 1 step
2. 2 steps
```

**Example 2:**

```
Input: 3
Output: 3
Explanation: There are three ways to climb to the top.
1. 1 step + 1 step + 1 step
2. 1 step + 2 steps
3. 2 steps + 1 step
```

**Solution**

```c++
class Solution {
public:
    int climbStairs(int n) {
        vector<int> dp(n+1,0);
        dp[0] = 1;
        dp[1] = 1;
        for(int i = 2; i <= n; ++i)
            dp[i] = dp[i-1]+dp[i-2];
        return dp[n];
    }
};
```



## 73. Set Matrix Zeroes

Medium

Given a *m* x *n* matrix, if an element is 0, set its entire row and column to 0. Do it [**in-place**](https://en.wikipedia.org/wiki/In-place_algorithm).

**Example 1:**

```
Input: 
[
  [1,1,1],
  [1,0,1],
  [1,1,1]
]
Output: 
[
  [1,0,1],
  [0,0,0],
  [1,0,1]
]
```

**Example 2:**

```
Input: 
[
  [0,1,2,0],
  [3,4,5,2],
  [1,3,1,5]
]
Output: 
[
  [0,0,0,0],
  [0,4,5,0],
  [0,3,1,0]
]
```

**Follow up:**

- A straight forward solution using O(*m**n*) space is probably a bad idea.
- A simple improvement uses O(*m* + *n*) space, but still not the best solution.
- Could you devise a constant space solution?

**Solution 1:** O(m+n) space

```c++
class Solution {
public:
    void setZeroes(vector<vector<int>>& matrix) {
        if (matrix.empty()) return;
        int m = matrix.size();
        int n = matrix[0].size();
        //O(m+n) space
        set<int> rowSet, colSet;
        for (int i = 0; i < m; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                if(!matrix[i][j])
                {
                    rowSet.insert(i);
                    colSet.insert(j);
                }
            }
        }
        ;
        for(auto row: rowSet)
        {
            vector<int> rowVec(n,0);
            matrix[row].swap(rowVec);
        }            
        for(auto col: colSet)
        {
            for (int i = 0; i < m; ++i)
            {
                matrix[i][col] = 0;
            }
        }
        return;
    }
};
```

**Improve:** O(1) space

```c++
class Solution {
public:
    void setZeroes(vector<vector<int>>& matrix) {
        if (matrix.empty()) return;
        int m = matrix.size(), n = matrix[0].size();
        //O(1) space
        bool col0 = false;//let matrix[0][0] represents row 0 state, col0 represents col 0 state
        for (int i = 0; i < m; ++i)
        {
            if (!matrix[i][0]) col0 = true;
            for (int j = 1; j < n; ++j)
            {                
                if(!matrix[i][j])
                    matrix[i][0] = matrix[0][j] = 0;
            }
        }
        for (int i = m-1; i >= 0; --i)
        {            
            for (int j = n-1; j >= 1; --j)
            {                
                if(!matrix[i][0] || !matrix[0][j])
                    matrix[i][j] = 0;
            }
            if (col0) matrix[i][0] = 0;
        }
        return;
    }
};
```



## 88. Merge Sorted Array

Easy

Given two sorted integer arrays *nums1* and *nums2*, merge *nums2* into *nums1* as one sorted array.

**Note:**

- The number of elements initialized in *nums1* and *nums2* are *m* and *n* respectively.
- You may assume that *nums1* has enough space (size that is greater or equal to *m* + *n*) to hold additional elements from *nums2*.

**Example:**

```
Input:
nums1 = [1,2,3,0,0,0], m = 3
nums2 = [2,5,6],       n = 3

Output: [1,2,2,3,5,6]
```

**Solution**

```c++
class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        int i = m-1, j = n-1, k = m+n-1;
        while(j >= 0)
            nums1[k--] = i >= 0 && nums1[i] > nums2[j] ? nums1[i--] : nums2[j--];        
        return;
    }
};
```



## 101. Symmetric Tree

Easy

Given a binary tree, check whether it is a mirror of itself (ie, symmetric around its center).

For example, this binary tree `[1,2,2,3,4,4,3]` is symmetric:

```
    1
   / \
  2   2
 / \ / \
3  4 4  3
```

 

But the following `[1,2,2,null,3,null,3]` is not:

```
    1
   / \
  2   2
   \   \
   3    3
```

 

**Note:**
Bonus points if you could solve it both recursively and iteratively.

```c++
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    bool isSymmetric(TreeNode* root) {
        //time O(n), space O(logn)
        return isSymmetric(root, root);
    }
private:
    bool isSymmetric(TreeNode* t1, TreeNode* t2) {
        if(t1 == NULL && t2 == NULL) return true;
        if(t1 == NULL || t2 == NULL) return false;
        return (t1->val==t2->val) && isSymmetric(t1->left,t2->right) && isSymmetric(t1->right,t2->left);
    }
};

class Solution {
public:
    bool isSymmetric(TreeNode* root) {
        //time O(n), space O(n)
        if(root==NULL) return true;
        queue<TreeNode*> queTree;
        queTree.push(root);
        queTree.push(root);
        while(queTree.size())
        {
            TreeNode* t1 = queTree.front();
            queTree.pop();
            TreeNode* t2 = queTree.front();
            queTree.pop();
            if(t1==NULL&&t2==NULL) continue;
            if(t1==NULL||t2==NULL) return false;
            if(t1->val!=t2->val) return false;
            queTree.push(t1->left);
            queTree.push(t2->right);
            queTree.push(t1->right);
            queTree.push(t2->left);
        }
        return true;
    }
};
```



## 104. Maximum Depth of Binary Tree

Easy

Given a binary tree, find its maximum depth.

The maximum depth is the number of nodes along the longest path from the root node down to the farthest leaf node.

**Note:** A leaf is a node with no children.

**Example:**

Given binary tree `[3,9,20,null,null,15,7]`,

```
    3
   / \
  9  20
    /  \
   15   7
```

return its depth = 3.

```c++
class Solution {
public:
    int maxDepth(TreeNode* root) {
        //time O(n), space O(logn)
        if(!root) return 0;
        int left = maxDepth(root->left);
        int right = maxDepth(root->right);
        return (left>right?left:right)+1;
    }
};
```



## 108. Convert Sorted Array to Binary Search Tree

Easy

Given an array where elements are sorted in ascending order, convert it to a height balanced BST.

For this problem, a height-balanced binary tree is defined as a binary tree in which the depth of the two subtrees of *every* node never differ by more than 1.

**Example:**

```
Given the sorted array: [-10,-3,0,5,9],

One possible answer is: [0,-3,9,-10,null,5], which represents the following height balanced BST:

      0
     / \
   -3   9
   /   /
 -10  5
```

```c++
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    TreeNode* sortedArrayToBST(vector<int>& nums) {
        //time O(n), space O(logn)
        return buildBST(nums, 0, nums.size()-1);
    }
private:
    //build BST from nums[begin,end], return root
    TreeNode* buildBST(vector<int>& nums, int begin, int end)
    {
        if(begin == end)
            return new TreeNode(nums[begin]);
        if(begin>end) return NULL;
        int mid = begin + (end-begin)/2;
        TreeNode* root = new TreeNode(nums[mid]);
        root->left = buildBST(nums, begin, mid-1);
        root->right = buildBST(nums, mid+1, end);
        return root;
    }
};
```



## 118. Pascal's Triangle

Easy

Given a non-negative integer *numRows*, generate the first *numRows* of Pascal's triangle.

![img](https://upload.wikimedia.org/wikipedia/commons/0/0d/PascalTriangleAnimated2.gif)
In Pascal's triangle, each number is the sum of the two numbers directly above it.

**Example:**

```
Input: 5
Output:
[
     [1],
    [1,1],
   [1,2,1],
  [1,3,3,1],
 [1,4,6,4,1]
]
```

```c++
class Solution {
public:
    vector<vector<int>> generate(int numRows) {
        vector<vector<int>> res(numRows);
        for(int i = 0; i < numRows; ++i)
        {
            res[i].resize(i+1);
            res[i][0] = res[i][i] = 1;
            for(int j = 1; j < i; ++j)
                res[i][j] = res[i-1][j-1]+res[i-1][j];
        }
        return res;
    }
};
```



## 121. Best Time to Buy and Sell Stock

Easy

Say you have an array for which the *i*th element is the price of a given stock on day *i*.

If you were only permitted to complete at most one transaction (i.e., buy one and sell one share of the stock), design an algorithm to find the maximum profit.

Note that you cannot sell a stock before you buy one.

**Example 1:**

```
Input: [7,1,5,3,6,4]
Output: 5
Explanation: Buy on day 2 (price = 1) and sell on day 5 (price = 6), profit = 6-1 = 5.
             Not 7-1 = 6, as selling price needs to be larger than buying price.
```

**Example 2:**

```
Input: [7,6,4,3,1]
Output: 0
Explanation: In this case, no transaction is done, i.e. max profit = 0.
```

```c++
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        //time O(n), space O(n)
        if(prices.empty()) return 0;
        int n = prices.size();
        vector<int> dp(n, 0);//dp[i] means on day i the maximum profit
        int buyMin = prices[0];
        for(int i = 1; i < n; ++i)
        {
            dp[i] = max(dp[i-1], prices[i]-buyMin);
            buyMin = min(buyMin, prices[i]);
        }
        return dp[n-1];
    }
};

class Solution {
public:
    int maxProfit(vector<int>& prices) {
        //time O(n), space O(1)
        if(prices.empty()) return 0;
        int n = prices.size();        
        int buyMin = prices[0];
        int maxPro = 0;
        for(int i = 1; i < n; ++i)
        {
            maxPro = max(maxPro, prices[i]-buyMin);
            buyMin = min(buyMin, prices[i]);
        }
        return maxPro;
    }
};
```



## 122. Best Time to Buy and Sell Stock II

Easy

Say you have an array for which the *i*th element is the price of a given stock on day *i*.

Design an algorithm to find the maximum profit. You may complete as many transactions as you like (i.e., buy one and sell one share of the stock multiple times).

**Note:** You may not engage in multiple transactions at the same time (i.e., you must sell the stock before you buy again).

**Example 1:**

```
Input: [7,1,5,3,6,4]
Output: 7
Explanation: Buy on day 2 (price = 1) and sell on day 3 (price = 5), profit = 5-1 = 4.
             Then buy on day 4 (price = 3) and sell on day 5 (price = 6), profit = 6-3 = 3.
```

**Example 2:**

```
Input: [1,2,3,4,5]
Output: 4
Explanation: Buy on day 1 (price = 1) and sell on day 5 (price = 5), profit = 5-1 = 4.
             Note that you cannot buy on day 1, buy on day 2 and sell them later, as you are
             engaging multiple transactions at the same time. You must sell before buying again.
```

**Example 3:**

```
Input: [7,6,4,3,1]
Output: 0
Explanation: In this case, no transaction is done, i.e. max profit = 0.
```

```c++
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        //time O(n), space O(n)
        if(prices.empty()) return 0;
        int n = prices.size();
        vector<int> dp(n, 0);//dp[i] means on day i the maximum profit
        int buyMin = prices[0];
        for(int i = 1; i < n; ++i)
        {
            if(prices[i]-buyMin > 0)
            {
                dp[i] = dp[i-1] + prices[i]-buyMin;
                buyMin = prices[i];
            }
            else
            {
                dp[i] = dp[i-1];
                buyMin = min(buyMin, prices[i]);
            }                
        }
        return dp[n-1];
    }
};

class Solution {
public:
    int maxProfit(vector<int>& prices) {
        //time O(n), space O(1)
        if(prices.empty()) return 0;
        int n = prices.size();
        int maxPro = 0;
        for(int i = 1; i < n; ++i)
        {
            if(prices[i] > prices[i-1])
                maxPro += prices[i]-prices[i-1];             
        }
        return maxPro;
    }
};
```



## 125. Valid Palindrome

Easy

Given a string, determine if it is a palindrome, considering only alphanumeric characters and ignoring cases.

**Note:** For the purpose of this problem, we define empty string as valid palindrome.

**Example 1:**

```
Input: "A man, a plan, a canal: Panama"
Output: true
```

**Example 2:**

```
Input: "race a car"
Output: false
```

**Solution:**

```c++
class Solution {
public:
    bool isPalindrome(string s) {
        //time O(n), space O(1)
        for(int i = 0, j = s.size()-1; i < j;)
        {
            if(isalnum(s[i]) && isalnum(s[j]))
            {
                if(tolower(s[i]) == tolower(s[j]))
                {
                    ++i;--j;
                    continue;
                }
                return false;
            }
            if(!isalnum(s[i]))
                ++i;
            if(!isalnum(s[j]))
                --j;
        }
        return true;
    }
};

class Solution {
public:
    bool isPalindrome(string s) {        
        //time O(n), space O(1)
        for (int i = 0, j = s.size() - 1; i < j; ++i, --j) 
        {
            while (isalnum(s[i]) == false && i < j) i++;    
            while (isalnum(s[j]) == false && i < j) j--; 
            if (toupper(s[i]) != toupper(s[j])) return false; 
        }
        return true;
    }
};
```



## 136. Single Number

Easy

Given a **non-empty** array of integers, every element appears *twice* except for one. Find that single one.

**Note:**

Your algorithm should have a linear runtime complexity. Could you implement it without using extra memory?

**Example 1:**

```
Input: [2,2,1]
Output: 1
```

**Example 2:**

```
Input: [4,1,2,1,2]
Output: 4
```

**Solution:**

```c++
class Solution {
public:
    int singleNumber(vector<int>& nums) {
        int res = 0;
        for (auto num: nums)
            res ^= num;
        return res;
    }
};
```



## 141. Linked List Cycle

Easy

Given a linked list, determine if it has a cycle in it.

To represent a cycle in the given linked list, we use an integer `pos` which represents the position (0-indexed) in the linked list where tail connects to. If `pos` is `-1`, then there is no cycle in the linked list.

 

**Example 1:**

```
Input: head = [3,2,0,-4], pos = 1
Output: true
Explanation: There is a cycle in the linked list, where tail connects to the second node.
```

![img](https://assets.leetcode.com/uploads/2018/12/07/circularlinkedlist.png)

**Example 2:**

```
Input: head = [1,2], pos = 0
Output: true
Explanation: There is a cycle in the linked list, where tail connects to the first node.
```

![img](https://assets.leetcode.com/uploads/2018/12/07/circularlinkedlist_test2.png)

**Example 3:**

```
Input: head = [1], pos = -1
Output: false
Explanation: There is no cycle in the linked list.
```

![img](https://assets.leetcode.com/uploads/2018/12/07/circularlinkedlist_test3.png)

 

**Follow up:**

Can you solve it using *O(1)* (i.e. constant) memory?

```c++
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    bool hasCycle(ListNode *head) {
        //time O(n), space O(1)
        ListNode* fast, *slow;
        fast = slow = head;
        while (fast && fast->next)
        {
            slow = slow->next;
            fast = fast->next->next;
            if (slow == fast)
                return true;
        }
        return false;
    }
};

class Solution {
public:
    bool hasCycle(ListNode *head) {
        //time O(n), space O(1)
        ListNode* dummyHead = new ListNode(-1);
        dummyHead->next = head;
        ListNode* fast, *slow;
        fast = slow = dummyHead;
        while (fast && fast->next)
        {
            slow = slow->next;
            fast = fast->next->next;
            if (slow == fast)
                return true;
        }
        return false;
    }
};

class Solution {
public:
    bool hasCycle(ListNode *head) {
        //time O(n), space O(1)
        ListNode* fast, *slow;
        fast = slow = head;
        while (fast && fast->next && fast->next->next && fast->next->next->next)
        {
            slow = slow->next;
            fast = fast->next->next->next->next;//fast = fast->next->next->next;// interesting! can be proved!
            if (slow == fast)
                return true;
        }
        return false;
    }
};
```



## 160. Intersection of Two Linked Lists

Easy

Write a program to find the node at which the intersection of two singly linked lists begins.

For example, the following two linked lists:

[![img](https://assets.leetcode.com/uploads/2018/12/13/160_statement.png)](https://assets.leetcode.com/uploads/2018/12/13/160_statement.png)

begin to intersect at node c1.

 

**Example 1:**

[![img](https://assets.leetcode.com/uploads/2018/12/13/160_example_1.png)](https://assets.leetcode.com/uploads/2018/12/13/160_example_1.png)

```
Input: intersectVal = 8, listA = [4,1,8,4,5], listB = [5,0,1,8,4,5], skipA = 2, skipB = 3
Output: Reference of the node with value = 8
Input Explanation: The intersected node's value is 8 (note that this must not be 0 if the two lists intersect). From the head of A, it reads as [4,1,8,4,5]. From the head of B, it reads as [5,0,1,8,4,5]. There are 2 nodes before the intersected node in A; There are 3 nodes before the intersected node in B.
```

 

**Example 2:**

[![img](https://assets.leetcode.com/uploads/2018/12/13/160_example_2.png)](https://assets.leetcode.com/uploads/2018/12/13/160_example_2.png)

```
Input: intersectVal = 2, listA = [0,9,1,2,4], listB = [3,2,4], skipA = 3, skipB = 1
Output: Reference of the node with value = 2
Input Explanation: The intersected node's value is 2 (note that this must not be 0 if the two lists intersect). From the head of A, it reads as [0,9,1,2,4]. From the head of B, it reads as [3,2,4]. There are 3 nodes before the intersected node in A; There are 1 node before the intersected node in B.
```

 

**Example 3:**

[![img](https://assets.leetcode.com/uploads/2018/12/13/160_example_3.png)](https://assets.leetcode.com/uploads/2018/12/13/160_example_3.png)

```
Input: intersectVal = 0, listA = [2,6,4], listB = [1,5], skipA = 3, skipB = 2
Output: null
Input Explanation: From the head of A, it reads as [2,6,4]. From the head of B, it reads as [1,5]. Since the two lists do not intersect, intersectVal must be 0, while skipA and skipB can be arbitrary values.
Explanation: The two lists do not intersect, so return null.
```

 

**Notes:**

- If the two linked lists have no intersection at all, return `null`.
- The linked lists must retain their original structure after the function returns.
- You may assume there are no cycles anywhere in the entire linked structure.
- Your code should preferably run in O(n) time and use only O(1) memory.

```c++
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        //max length is n, time O(n+m) = O(n), space O(1)
        if(headA == NULL || headB == NULL) return NULL;
        //if(headA == headB) return headA;
        ListNode* p1 = headA;
        ListNode* p2 = headB;
        while(p1 != NULL && p2 != NULL && p1 != p2/*avoid head is entry*/)
        {
            p1 = p1->next;
            p2 = p2->next;
            if(p1 == p2) return p1;
            if(p1 == NULL) p1 = headA;
            if(p2 == NULL) p2 = headB;
            //if(p1 == p2) return p1;
        }
        return p1;
    }
};

class Solution {
public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        //max length is n, time O(n+m) = O(n), space O(1)
        if(headA == NULL || headB == NULL) return NULL;
        ListNode* d1 = new ListNode(0);
        ListNode* d2 = new ListNode(0);
        d1->next = headA, d2->next = headB;
        ListNode* p1 = d1;
        ListNode* p2 = d2;
        while(p1 != NULL && p2 != NULL)
        {
            p1 = p1->next;
            p2 = p2->next;
            if(p1 == p2) return p1;
            if(p1 == NULL) p1 = d2;
            if(p2 == NULL) p2 = d1;
            
        }
        return p1;
    }
};
```



## 169. Majority Element

Easy

Given an array of size *n*, find the majority element. The majority element is the element that appears **more than** `⌊ n/2 ⌋` times.

You may assume that the array is non-empty and the majority element always exist in the array.

**Example 1:**

```
Input: [3,2,3]
Output: 3
```

**Example 2:**

```
Input: [2,2,1,1,1,2,2]
Output: 2
```

```c++
class Solution {
public:
    int majorityElement(vector<int>& nums) {
        //time O(nlogn), space O(1)
        sort(nums.begin(), nums.end());
        return nums[nums.size()/2];
    }
};	

class Solution {
public:
    int majorityElement(vector<int>& nums) {
        //time O(n), space O(n)
        unordered_map<int, int> record;
        for(auto num: nums)
            ++record[num];
        auto res = record.begin();
        for(auto iter=record.begin(), end = record.end(); iter != end; ++iter)
        {
            if(iter->second > res->second)
                res = iter;
        }
        return res->first;
    }
};

class Solution {
public:
    int majorityElement(vector<int>& nums) {
        //time O(n), space O(1)
        int major = nums[0], count = 1;
        for(int i = 1; i < nums.size(); ++i)
        {
            if(!count)
            {
                ++count;
                major = nums[i];
            }
            else if(nums[i] == major)
                ++count;
            else//if(nums[i] != major)
                --count;
            
        }
        return major;
    }
};

class Solution {
public:
    int majorityElement(vector<int>& nums) {
        //time O(nlogn), space O(logn)
        return majority(nums, 0, nums.size()-1);
    }
private:
    int majority(vector<int>& nums, int l, int r) {
        if(l == r)
            return nums[l];
        int mid = l + (r-l)/2;
        int lm = majority(nums,l,mid), rm = majority(nums, mid+1, r);
        if(lm == rm)
            return lm;
        return count(nums.begin()+l, nums.begin()+r+1, lm) > count(nums.begin()+l, nums.begin()+r+1, rm) ? lm : rm;
    }
};
```



## 171. Excel Sheet Column Number

Easy

Given a column title as appear in an Excel sheet, return its corresponding column number.

For example:

```
    A -> 1
    B -> 2
    C -> 3
    ...
    Z -> 26
    AA -> 27
    AB -> 28 
    ...
```

**Example 1:**

```
Input: "A"
Output: 1
```

**Example 2:**

```
Input: "AB"
Output: 28
```

**Example 3:**

```
Input: "ZY"
Output: 701
```

```c++
class Solution {
public:
    int titleToNumber(string s) {
        int size = s.size();
        int res = 0;
        for(int i = 0; i < size; ++i)
            res = 26*res + (s[i]-'A'+1);//may overflow, so use () or put first
        return res;
    }
};

```

```c++
class Solution {
public:
    int titleToNumber(string s) {
        int col = 0;
        for(int i = s.length()-1; i >= 0; i--) {             
            col += (s[i] - 'A' + 1) * pow(26, (s.length()-1- i));
        }
        return col;
    }
};

```



## 172. Factorial Trailing Zeroes

Easy

Given an integer *n*, return the number of trailing zeroes in *n*!.

**Example 1:**

```
Input: 3
Output: 0
Explanation: 3! = 6, no trailing zero.
```

**Example 2:**

```
Input: 5
Output: 1
Explanation: 5! = 120, one trailing zero.
```

**Note:** Your solution should be in logarithmic time complexity.

```c++
class Solution {
public:
    int trailingZeroes(int n) {
        int res = 0;
        while(n)
        {
            n /= 5;
            res += n;	
        }
        return res;
    }
};

class Solution {
public:
    int trailingZeroes(int n) {
        return n ? n/5+trailingZeroes(n/5) : 0;
    }
};
```



## 189. Rotate Array

Easy

Given an array, rotate the array to the right by *k* steps, where *k* is non-negative.

**Example 1:**

```
Input: [1,2,3,4,5,6,7] and k = 3
Output: [5,6,7,1,2,3,4]
Explanation:
rotate 1 steps to the right: [7,1,2,3,4,5,6]
rotate 2 steps to the right: [6,7,1,2,3,4,5]
rotate 3 steps to the right: [5,6,7,1,2,3,4]
```

**Example 2:**

```
Input: [-1,-100,3,99] and k = 2
Output: [3,99,-1,-100]
Explanation: 
rotate 1 steps to the right: [99,-1,-100,3]
rotate 2 steps to the right: [3,99,-1,-100]
```

**Note:**

- Try to come up as many solutions as you can, there are at least 3 different ways to solve this problem.
- Could you do it in-place with O(1) extra space?

```c++
class Solution {
public:
    void rotate(vector<int>& nums, int k) {
        //time O(n),sapce O(1)
        if(nums.empty()) return;
        int n = nums.size();
        k %= n;
        if(k == 0) return;
        reverse(nums.begin(),nums.begin()+(n-k));
        reverse(nums.begin()+(n-k),nums.end());
        reverse(nums.begin(),nums.end());
        return;
    }
};
class Solution {
public:
    void rotate(vector<int>& nums, int k) {
        //time O(n),sapce O(1)
        if(nums.empty()) return;
        int n = nums.size();
        k %= n;
        if(k == 0) return;
        reverse(nums.begin(),nums.end());
        reverse(nums.begin(),nums.begin()+k);
        reverse(nums.begin()+k,nums.end());        
        return;
    }
};
class Solution {
public:
    void rotate(vector<int>& nums, int k) {
        //time O(n),sapce O(n)
        if(nums.empty()) return;
        int n = nums.size();
        k %= n;
        if(k == 0) return;
        nums.insert(nums.end(), nums.begin(),nums.begin()+(n-k));
        nums.erase(nums.begin(),nums.begin()+(n-k));
        return;
    }
};

```



## 190. Reverse Bits

Easy

Reverse bits of a given 32 bits unsigned integer.

 

**Example 1:**

```
Input: 00000010100101000001111010011100
Output: 00111001011110000010100101000000
Explanation: The input binary string 00000010100101000001111010011100 represents the unsigned integer 43261596, so return 964176192 which its binary representation is 00111001011110000010100101000000.
```

**Example 2:**

```
Input: 11111111111111111111111111111101
Output: 10111111111111111111111111111111
Explanation: The input binary string 11111111111111111111111111111101 represents the unsigned integer 4294967293, so return 3221225471 which its binary representation is 10111111111111111111111111111111.
```

 

**Note:**

- Note that in some languages such as Java, there is no unsigned integer type. In this case, both input and output will be given as signed integer type and should not affect your implementation, as the internal binary representation of the integer is the same whether it is signed or unsigned.
- In Java, the compiler represents the signed integers using [2's complement notation](https://en.wikipedia.org/wiki/Two's_complement). Therefore, in **Example 2** above the input represents the signed integer `-3` and the output represents the signed integer `-1073741825`.

 

**Follow up**:

If this function is called many times, how would you optimize it?

```c++
class Solution {
public:
    uint32_t reverseBits(uint32_t n) {
        //time O(bits), space O(1)
        uint32_t result = 0;
        for(int i = 0; i < 32; ++i)
        {
            result = (result << 1) + ((n >> i) & 1);
        }
        return result;
    }
};

class Solution {
public:
    uint32_t reverseBits(uint32_t n) {
        //time O(log(bits)), space O(1)
        n = n >> 16 | n << 16;
        n = (n & 0xFF00FF00) >> 8 | (n & 0x00FF00FF) << 8;
        n = (n & 0xF0F0F0F0) >> 4 | (n & 0x0F0F0F0F) << 4;// abcd efgh --> efgh abcd
        n = (n & 0xCCCCCCCC) >> 2 | (n & 0x33333333) << 2;// efgh abcd --> ghef cdab
        n = (n & 0xAAAAAAAA) >> 1 | (n & 0x55555555) << 1;// ghef cdab --> hgfe dcba
        return n;
    }
};
```



## 191. Number of 1 Bits

Easy

Write a function that takes an unsigned integer and return the number of '1' bits it has (also known as the [Hamming weight](http://en.wikipedia.org/wiki/Hamming_weight)).

 

**Example 1:**

```
Input: 00000000000000000000000000001011
Output: 3
Explanation: The input binary string 00000000000000000000000000001011 has a total of three '1' bits.
```

**Example 2:**

```
Input: 00000000000000000000000010000000
Output: 1
Explanation: The input binary string 00000000000000000000000010000000 has a total of one '1' bit.
```

**Example 3:**

```
Input: 11111111111111111111111111111101
Output: 31
Explanation: The input binary string 11111111111111111111111111111101 has a total of thirty one '1' bits.
```

 

**Note:**

- Note that in some languages such as Java, there is no unsigned integer type. In this case, the input will be given as signed integer type and should not affect your implementation, as the internal binary representation of the integer is the same whether it is signed or unsigned.
- In Java, the compiler represents the signed integers using [2's complement notation](https://en.wikipedia.org/wiki/Two's_complement). Therefore, in **Example 3** above the input represents the signed integer `-3`.

 

**Follow up**:

If this function is called many times, how would you optimize it?

```c++
class Solution {
public:
    int hammingWeight(uint32_t n) {
        //time O(1), space O(1)
        int result = 0;
        while(n)
        {
            ++result;
            n &= (n-1);
        }
        return result;
    }
};
```



## 198. House Robber

Easy

You are a professional robber planning to rob houses along a street. Each house has a certain amount of money stashed, the only constraint stopping you from robbing each of them is that adjacent houses have security system connected and **it will automatically contact the police if two adjacent houses were broken into on the same night**.

Given a list of non-negative integers representing the amount of money of each house, determine the maximum amount of money you can rob tonight **without alerting the police**.

**Example 1:**

```
Input: [1,2,3,1]
Output: 4
Explanation: Rob house 1 (money = 1) and then rob house 3 (money = 3).
             Total amount you can rob = 1 + 3 = 4.
```

**Example 2:**

```
Input: [2,7,9,3,1]
Output: 12
Explanation: Rob house 1 (money = 2), rob house 3 (money = 9) and rob house 5 (money = 1).
             Total amount you can rob = 2 + 9 + 1 = 12.
```

```c++
class Solution {
public:
    int rob(vector<int>& nums) {
        if(nums.empty()) return 0;
        //time O(n), space O(n^2)
        int size = nums.size();
        vector<int> dp(size, 0);//dp[i] means the maximum amout when rob nums[i] 
        int result = 0;
        for(int i = 0; i < size; ++i)
        {
            dp[i] = nums[i];
            if(i >= 2)
            {
                int rangeMax = 0;
                for(int j = 0; j <= i - 2; ++j)
                    rangeMax = max(rangeMax, dp[j]);
                dp[i] += rangeMax;
            }                
            result = max(result, dp[i]);
        }
        return result;
    }
};

class Solution {
public:
    int rob(vector<int>& nums) {
        if(nums.empty()) return 0;
        //time O(n), space O(n^2)
        int n = nums.size();        
        vector<int> memo(n,-1);////memo[i]：从i~n-1偷到的最大物品价值
        memo[n-1]=nums[n-1];//init
        for(int i=n-2;i>=0;i--){
            for(int j=i;j<n;j++){
                memo[i]=max( memo[i],nums[j]+(j+2<=n-1?memo[j+2]:0) );
            }
        }
        return memo[0];
    }
};

TODO: https://leetcode.com/problems/house-robber/discuss/156523/From-good-to-great.-How-to-approach-most-of-DP-problems.
```



## 202. Happy Number

Easy

Write an algorithm to determine if a number is "happy".

A happy number is a number defined by the following process: Starting with any positive integer, replace the number by the sum of the squares of its digits, and repeat the process until the number equals 1 (where it will stay), or it loops endlessly in a cycle which does not include 1. Those numbers for which this process ends in 1 are happy numbers.

**Example:** 

```
Input: 19
Output: true
Explanation: 
12 + 92 = 82
82 + 22 = 68
62 + 82 = 100
12 + 02 + 02 = 1
```

```c++
class Solution {
public:
    bool isHappy(int n) {
        //time O(?), space O(?)
        if(record.find(n) != record.end())
            return false;
        int next = Cal(n);
        if(next == 1) return true;
        record.insert(n);
        return isHappy(next);
    }
private:
    int Cal(int n)
    {
        int result = 0;
        while(n)
        {            
            result += (n % 10)*(n % 10);
            n /= 10;
        }
        return result;
    }
    set<int> record;
};

class Solution {
public:
    bool isHappy(int n) {
        //time O(?), space O(1)
        int slow, fast;
        slow = fast = n;
        do {
            slow = digitSquareSum(slow);
            fast = digitSquareSum(fast);
            fast = digitSquareSum(fast);
            if(fast == 1) return 1;
        } while(slow != fast);
         return 0;
    }
private:
    int digitSquareSum(int n)
    {
        int result = 0;
        while(n)
        {            
            result += (n % 10)*(n % 10);
            n /= 10;
        }
        return result;
    }
};
```



## 204. Count Primes

Easy

Count the number of prime numbers less than a non-negative number, ***n\***.

**Example:**

```
Input: 10
Output: 4
Explanation: There are 4 prime numbers less than 10, they are 2, 3, 5, 7.
```

```c++
class Solution {
public:
    int countPrimes(int n) {
        //time O(n^1.5), space O(1)
        int count = 0;
        for (int i = 1; i < n; i++) {
            if (isPrime(i)) count++;
        }
        return count;
    }
private:
    bool isPrime(int num) {
        if (num <= 1) return false;
        // Loop's ending condition is i * i <= num instead of i <= sqrt(num)
        // to avoid repeatedly calling an expensive function sqrt().
        for (int i = 2; i * i <= num; i++) {
            if (num % i == 0) return false;
        }
        return true;
    }
};

class Solution {
public:
    int countPrimes(int n) {
        //time O(nloglogn), space O(n)
        vector<bool> isPrime(n, true);//isPrime[i] means i is or not a prime number, actually 0 and 1 are false
        //less than n, not less equal
        for (int i = 2; i * i < n; i++) {
          if (!isPrime[i]) continue;
          for (int j = i * i; j < n; j += i) {
             isPrime[j] = false;
          }
        } 
        int count = 0;
        for (int i = 2; i < n; i++) {
            if (isPrime[i]) ++count;
        }
        return count;
    }
};
```



## 283. Move Zeroes

Easy

Given an array `nums`, write a function to move all `0`'s to the end of it while maintaining the relative order of the non-zero elements.

**Example:**

```
Input: [0,1,0,3,12]
Output: [1,3,12,0,0]
```

**Note**:

1. You must do this **in-place** without making a copy of the array.
2. Minimize the total number of operations.

**Solution:**

```c++
class Solution {
public:
    void moveZeroes(vector<int>& nums) {
        int size = nums.size(), count = 0;
        for (int i = 0; i < size; ++i)
        {
            if(nums[i] == 0)
                ++count;
            else
                if (count)
                    swap(nums[i-count], nums[i]);
        }
        return;
    }
};
```

**Improve:**

```c++
class Solution {
public:
    void moveZeroes(vector<int>& nums) {
        int zeroStart = 0, size = nums.size();//[0, zeroStart) [zeroStart,size)
        for (int i = 0; i < size; ++i)
        {
            if(nums[i])
                swap(nums[i], nums[zeroStart++]);
        }
        return;
    }
};
```

