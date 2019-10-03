[TOC]



# Array

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
        unordered_map<int,int> valIndexMap;        
        for (int i = 0; i < nums.size(); ++i)
        {
            auto iter = valIndexMap.find(target-nums[i]);
            if (iter == valIndexMap.end())
            {
                valIndexMap.insert(pair<int,int>(nums[i],i));
            }
            else
            {                   
                return vector<int>{iter->second, i};
            }
        }
        throw "no solution";
    }
};
```

**Improve:**

```c++
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
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

## 27. Remove Element

Easy

Given an array *nums* and a value *val*, remove all instances of that value [**in-place**](https://en.wikipedia.org/wiki/In-place_algorithm) and return the new length.

Do not allocate extra space for another array, you must do this by **modifying the input array in-place** with O(1) extra memory.

The order of elements can be changed. It doesn't matter what you leave beyond the new length.

**Example 1:**

```
Given nums = [3,2,2,3], val = 3,

Your function should return length = 2, with the first two elements of nums being 2.

It doesn't matter what you leave beyond the returned length.
```

**Example 2:**

```
Given nums = [0,1,2,2,3,0,4,2], val = 2,

Your function should return length = 5, with the first five elements of nums containing 0, 1, 3, 0, and 4.

Note that the order of those five elements can be arbitrary.

It doesn't matter what values are set beyond the returned length.
```

**Clarification:**

Confused why the returned value is an integer but your answer is an array?

Note that the input array is passed in by **reference**, which means modification to the input array will be known to the caller as well.

Internally you can think of this:

```
// nums is passed in by reference. (i.e., without making a copy)
int len = removeElement(nums, val);

// any modification to nums in your function would be known by the caller.
// using the length returned by your function, it prints the first len elements.
for (int i = 0; i < len; i++) {
    print(nums[i]);
}
```

**Solution 1:**  disorder

```c++
class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        int left = 0, right = nums.size()-1;
        while(left <= right)
        {
            if(nums[left] == val)
                swap(nums[left], nums[right--]);
            else
                ++left;
        }
        return left;
    }
};
```

**Solution 2:** order

```c++
class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        int size = nums.size(), count = 0;
        for (int i = 0; i < size; ++i)
        {
            if(nums[i] == val)
                ++count;
            else
            {
                if (count)
                    nums[i-count] = nums[i];
            }
        }
        return size-count;
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
        //!nums.empty() always success
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
        int size = nums.size(), res = INT_MIN;
        vector<int> dp(size+1, INT_MIN);//dp[i] means the maximum subarray ending with nums[i-1];
        for (int i = 1; i <= size; ++i)
        {
            dp[i] = dp[i-1] >= 0 ? dp[i-1] + nums[i-1] : max(dp[i-1], nums[i-1]);
            res = max(res, dp[i]);
        }
        return res;
    }
};
```

**Improve**: divide and conquer



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

**Solution:**

```c++
class Solution {
public:
    vector<int> plusOne(vector<int>& digits) {
        //vector<int> res;
        int size = digits.size();
        int carry = 1;
        for (int i = size - 1; i >= 0; --i)
        {
            int sum = digits[i] + carry;
            digits[i] = sum % 10;
            carry = sum / 10;
        }
        if (carry)
        {
            digits.insert(digits.begin(), carry);
        }
        return digits;
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



## 496. Next Greater Element I

Easy

You are given two arrays **(without duplicates)** `nums1` and `nums2` where `nums1`’s elements are subset of `nums2`. Find all the next greater numbers for `nums1`'s elements in the corresponding places of `nums2`.

The Next Greater Number of a number **x** in `nums1` is the first greater number to its right in `nums2`. If it does not exist, output -1 for this number.

**Example 1:**

```
Input: nums1 = [4,1,2], nums2 = [1,3,4,2].
Output: [-1,3,-1]
Explanation:
    For number 4 in the first array, you cannot find the next greater number for it in the second array, so output -1.
    For number 1 in the first array, the next greater number for it in the second array is 3.
    For number 2 in the first array, there is no next greater number for it in the second array, so output -1.
```

**Example 2:**

```
Input: nums1 = [2,4], nums2 = [1,2,3,4].
Output: [3,-1]
Explanation:
    For number 2 in the first array, the next greater number for it in the second array is 3.
    For number 4 in the first array, there is no next greater number for it in the second array, so output -1.
```

**Note:**

1. All elements in `nums1` and `nums2` are unique.
2. The length of both `nums1` and `nums2` would not exceed 1000.

**Solution:**

```c++
class Solution {
public:
    vector<int> nextGreaterElement(vector<int>& nums1, vector<int>& nums2) {
        unordered_map<int, int> nextGreater;
        int size2 = nums2.size();
        for (int i = 0; i < size2; ++i)
        {
            for (int j = i+1; j < size2; ++j)
            {
                if (nums2[j] > nums2[i])
                {
                    nextGreater[nums2[i]] = nums2[j];
                    break;
                }                    
            }
            if (nextGreater.find(nums2[i]) == nextGreater.end())
                nextGreater[nums2[i]] = -1;
        }
        int size1 = nums1.size();
        for (int i = 0; i < size1; ++i)
            nums1[i] = nextGreater[nums1[i]];
        return nums1;
    }
};
```

**Improved:**

```c++
class Solution {
public:
    vector<int> nextGreaterElement(vector<int>& nums1, vector<int>& nums2) {
        stack<int> stk;
        unordered_map<int, int> nextGreater;
        int size2 = nums2.size();
        for(int i = 0; i < size2; ++i)
        {
            while(!stk.empty() && stk.top() < nums2[i])
            {
                nextGreater[stk.top()] = nums2[i];
                stk.pop();
            }
            stk.push(nums2[i]);
        }
        int size1 = nums1.size();
        for (int i = 0; i < size1; ++i)
            nums1[i] = nextGreater.count(nums1[i]) ? nextGreater[nums1[i]] : -1;         
        return nums1;
    }
};

```



## 503. Next Greater Element II

Medium

Given a circular array (the next element of the last element is the first element of the array), print the Next Greater Number for every element. The Next Greater Number of a number x is the first greater number to its traversing-order next in the array, which means you could search circularly to find its next greater number. If it doesn't exist, output -1 for this number.

**Example 1:**

```
Input: [1,2,1]
Output: [2,-1,2]
Explanation: The first 1's next greater number is 2; The number 2 can't find next greater number; The second 1's next greater number needs to search circularly, which is also 2.
```

**Note:** The length of given array won't exceed 10000.

```c++
class Solution {
public:
    vector<int> nextGreaterElements(vector<int>& nums) {        
        int size = nums.size();
        vector<int> res(size, -1);
        for (int i = 0; i < size; ++i)
        {
            bool find = false;
            for (int j = i+1; j < size; ++j)
            {
                if (nums[j] > nums[i])
                {
                    res[i] = nums[j];
                    find = true;
                    break;
                }                    
            }
            if (!find)
            {
                for (int j = 0; j < i; ++j)
                {                    
                    if (nums[j] > nums[i])
                    {
                        res[i] = nums[j];
                        find = true;
                        break;
                    }                 
                }
            }
        }
        return res;
    }
};
```

**Improved:**

```C++
class Solution {
public:
    vector<int> nextGreaterElements(vector<int>& nums) {
        int size = nums.size();
        vector<int> res(size, 0);
        stack<int> stk;                
        for(int i = 2*size - 1; i >= 0; --i)
        {
            while(!stk.empty() && nums[stk.top()] <= nums[i%size])
                stk.pop();
            res[i%size] = stk.empty() ? -1: nums[stk.top()];
            stk.push(i%size);
        }
        return res;
    }
};
```



## 739. Daily Temperatures

Medium

Given a list of daily temperatures `T`, return a list such that, for each day in the input, tells you how many days you would have to wait until a warmer temperature. If there is no future day for which this is possible, put `0` instead.

For example, given the list of temperatures `T = [73, 74, 75, 71, 69, 72, 76, 73]`, your output should be `[1, 1, 4, 2, 1, 1, 0, 0]`.

**Note:** The length of `temperatures` will be in the range `[1, 30000]`. Each temperature will be an integer in the range `[30, 100]`.

**Solution:**

```c++
class Solution {
public:
    vector<int> dailyTemperatures(vector<int>& T) {
        int size = T.size();
        vector<int> res(size, 0);
        vector<int> next(101, INT_MAX);//next[i] means i temperatures appear first index in T reverse order
        for (int i = size - 1; i >= 0; --i)
        {
            int warm_index = INT_MAX;
            for (int j = T[i] + 1; j <= 100; ++j)
            {
                if (next[j] < warm_index)
                {
                    warm_index = next[j];
                }
            }
            if (warm_index < INT_MAX)
                res[i] = warm_index - i;
            next[T[i]] = i;
        }
        return res;
    }
};
```

**Improved:**



# Linked List

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



# String

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
        if (strs.empty())   return "";
        string minSizeString(strs[0]);
        for (auto str : strs)
        {
            if(str.length() < minSizeString.length())
            {
                minSizeString = str;
            }
        }
        int minCount = minSizeString.length();
        for (auto str : strs)
        {
            int size = commonPrefixSizeOfTwoString(str, minSizeString);
            if(size == 0)
            {
                return "";
            }
            else if (size < minCount)
            {
                minCount = size;
            }
        }
        return minSizeString.substr(0, minCount);
    }
private:
    int commonPrefixSizeOfTwoString(string str1, string str2)
    {
        int size = min(str1.length(), str2.length());
        int i = 0;
        while(i < size)
        {
            if (str1[i] != str2[i])
                break;
            ++i;
        }
        return i;
    }
};
```

**Improve:**

```c++
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
        if (needle.empty()) return 0;
        int hsize = haystack.size(), nsize = needle.size();
        if (nsize > hsize) return -1;
        int i = 0, j = 0;
        while (i < hsize && j < nsize)
        {
            if (haystack[i] == needle[j])
            {
                ++i;
                ++j;
            }
            else
            {
                i -= j;
                j = 0;
                ++i;
            }
        }        
        if (j == nsize)
            return i - j;
        return -1;
    }
};
```

**Improved:**



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
        if (s.empty()) return true;
        int left = 0, right = s.length()-1;
        while(left < right)
        {
            while( !isAlphanumeric(s[left]) && left < right)
                ++left;                
            while( !isAlphanumeric(s[right]) && left < right)
                --right;
            if (tolower(s[left]) != tolower(s[right]))
                return false;
            ++left;
            --right;
        }
        return true;
    }
private:
    bool isAlphanumeric(char ch)
    {
        return (tolower(ch) >= 'a' && tolower(ch) <= 'z') || (ch >= '0'&& ch <= '9');
    }
};
```

**Improve:**

```c++
class Solution {
public:
    bool isPalindrome(string s) {
    // Move 2 pointers from each end until they collide
    for (int i = 0, j = s.size() - 1; i < j; i++, j--) {    
        // Increment left pointer if not alphanumeric
        while (isalnum(s[i]) == false && i < j) i++;    
        // Decrement right pointer if no alphanumeric
        while (isalnum(s[j]) == false && i < j) j--; 
        // Exit and return error if not match
        if (toupper(s[i]) != toupper(s[j])) return false; 
    }
    return true;
}
};
```



# Bit Manipulation

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
        {
            res ^= num;
        }
        return res;
    }
};
```

## 137. Single Number II

Medium

Given a **non-empty** array of integers, every element appears *three* times except for one, which appears exactly once. Find that single one.

**Note:**

Your algorithm should have a linear runtime complexity. Could you implement it without using extra memory?

**Example 1:**

```
Input: [2,2,3,2]
Output: 3
```

**Example 2:**

```
Input: [0,1,0,1,0,1,99]
Output: 99
```

**Solution:** 

using extra memory

```c++
class Solution {
public:
    int singleNumber(vector<int>& nums) {        
        if(nums.empty()) return 0;
        unordered_map<int,int> record;
        int size = nums.size();
        for(int i = 0; i < size; ++i)
        {
            record[nums[i]]++;//default value = 0
        }
        auto iter = record.begin();
        for(; iter != record.end(); ++iter)
            if(iter->second == 1)
                break;
        return iter->first;
    }
};
```

**Improved:**

```c++
class Solution {
public:
    int singleNumber(vector<int>& nums) {        
        int x1 = 0, x2 = 0, mask = 0;
        int size = nums.size();
        for(int i = 0; i < size; ++i)
        {
            x2 ^= x1 & nums[i];
            x1 ^= nums[i];
            mask = ~(x2 & x1);
            x2 &= mask;
            x1 &= mask;
        }
        return x2|x1;
    }
};
```



## 260. Single Number III

Medium

Given an array of numbers `nums`, in which exactly two elements appear only once and all the other elements appear exactly twice. Find the two elements that appear only once.

**Example:**

```
Input:  [1,2,1,3,2,5]
Output: [3,5]
```

**Note**:

1. The order of the result is not important. So in the above example, `[5, 3]` is also correct.
2. Your algorithm should run in linear runtime complexity. Could you implement it using only constant space complexity?

**Solution:**

```c++
class Solution {
public:
    vector<int> singleNumber(vector<int>& nums) {
        int diff = accumulate(nums.begin(), nums.end(), 0, bit_xor<int>());
        diff &= -diff;
        vector<int> res{0,0};
        for (auto num: nums)
        {
            if (num & diff)
                res[0] ^= num;
            else
                res[1] ^= num;
        }
        return res;
    }
};
```



## 389. Find the Difference

Easy

Given two strings **s** and **t** which consist of only lowercase letters.

String **t** is generated by random shuffling string **s** and then add one more letter at a random position.

Find the letter that was added in **t**.

**Example:**

```
Input:
s = "abcd"
t = "abcde"

Output:
e

Explanation:
'e' is the letter that was added.
```

**Solution:**

```c++
class Solution {
public:
    char findTheDifference(string s, string t) {
        char res = 0;
        for (auto ch: s)
            res ^= ch;
        for (auto ch: t)
            res ^= ch;
        return res;
    }
};
```



# Math

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
            else 
            {
                if (mid+1 > x/(mid + 1))
                    return mid;
                left = mid + 1;
            }
        }
    }
};
```



## 367. Valid Perfect Square

Easy

Given a positive integer *num*, write a function which returns True if *num* is a perfect square else False.

**Note:** **Do not** use any built-in library function such as `sqrt`.

**Example 1:**

```
Input: 16
Output: true
```

**Example 2:**

```
Input: 14
Output: false
```

**Solution:**

```c++
class Solution {
public:
    bool isPerfectSquare(int num) {
        int left = 1, right = num/2;
        while (true) 
        {
            int mid = left + (right-left)/2;
            if (mid == num/mid)
            {
                if (mid != (num-1)/mid)
                    return true;
                return false;
            }
            else if (mid > num/mid)
                right = mid - 1;
            else//mid*mid < num
            {
                if ((mid+1) > num/(mid+1))
                    return false;
                left = mid + 1;
            }
        }
    }
};
```

