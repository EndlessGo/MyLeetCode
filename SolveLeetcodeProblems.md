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



## 3. Longest Substring Without Repeating Characters

Medium

Given a string, find the length of the **longest substring** without repeating characters.

**Example 1:**

```
Input: "abcabcbb"
Output: 3 
Explanation: The answer is "abc", with the length of 3. 
```

**Example 2:**

```
Input: "bbbbb"
Output: 1
Explanation: The answer is "b", with the length of 1.
```

**Example 3:**

```
Input: "pwwkew"
Output: 3
Explanation: The answer is "wke", with the length of 3. 
             Note that the answer must be a substring, "pwke" is a subsequence and not a substring.
```

**Solution:** O(n) time.

```c++
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        vector<bool> appear(256, false);        
        int size = s.size(), length = 0;
        //s[i...j] store without repeating characters
        int i = 0, j = -1;
        while(i < size)
        {
            if(j+1 < size && !appear[s[j+1]])
                appear[s[++j]] = true;
            else//j+1 >= size || appear[s[++j]]
                appear[s[i++]] = false;
            length = max(length, j-i+1);
        }
        return length;
    }
};
```



## 11. Container With Most Water

Medium

Given *n* non-negative integers *a1*, *a2*, ..., *an* , where each represents a point at coordinate (*i*, *ai*). *n* vertical lines are drawn such that the two endpoints of line *i* is at (*i*, *ai*) and (*i*, 0). Find two lines, which together with x-axis forms a container, such that the container contains the most water.

**Note:** You may not slant the container and *n* is at least 2.

 

![img](https://s3-lc-upload.s3.amazonaws.com/uploads/2018/07/17/question_11.jpg)

The above vertical lines are represented by array [1,8,6,2,5,4,8,3,7]. In this case, the max area of water (blue section) the container can contain is 49.

 

**Example:**

```
Input: [1,8,6,2,5,4,8,3,7]
Output: 49
```

**Solution:**

```c++
class Solution {
public:
    int maxArea(vector<int>& height) {
        int l = 0, r = height.size()-1;
        int shorter = min(height[l], height[r]);
        int maxArea = (r-l)*shorter;
        //compute max area in height[l...r]
        while(l < r)
        {
            if(height[l] < height[r])
            {
                ++l;
                if(height[l] > shorter)
                {
                    shorter = min(height[l], height[r]);
                    maxArea = max(maxArea, (r-l)*shorter);
                }
                    
            }
            else
            {
                --r;
                if(height[r] > shorter)
                {
                    shorter = min(height[l], height[r]);
                    maxArea = max(maxArea, (r-l)*shorter);
                }
            }
        }
        return maxArea;
    }
};
```

**Improve:**

```c++
class Solution {
public:
    int maxArea(vector<int>& height) {
        int l = 0, r = height.size()-1;
        int maxArea = 0, shorter = 0;
        //compute max area in height[l...r]
        while(l < r)
        {
            shorter = min(height[l], height[r]);
            maxArea = max(maxArea, (r-l)*shorter);
            while(l < r && height[l] <= shorter)
                ++l;
            while(l < r && height[r] <= shorter)
                --r;
        }
        return maxArea;
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

**Clarification:**

Confused why the returned value is an integer but your answer is an array?

Note that the input array is passed in by **reference**, which means modification to the input array will be known to the caller as well.

Internally you can think of this:

```
// nums is passed in by reference. (i.e., without making a copy)
int len = removeDuplicates(nums);

// any modification to nums in your function would be known by the caller.
// using the length returned by your function, it prints the first len elements.
for (int i = 0; i < len; i++) {
    print(nums[i]);
}
```

**Solution 1:**

```c++
class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        int k = 0, size = nums.size();//nums[0...k) store appear once element
        for(int i = 0; i < size; ++i)
        {
            if(i > 0 && nums[i] == nums[i-1])
                continue;
            nums[k++] = nums[i];
        }
        return k;
    }
};

class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        int size = nums.size();
        if(size == 0 || size == 1) return size;
        int k = 1;//nums[0...k) store appear once element
        for(int i = 1; i < size; ++i)
        {
            if(nums[i] == nums[i-1])
                continue;
            nums[k++] = nums[i];
        }
        return k;
    }
};

class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        if(nums.empty()) return 0;
        int k = 1, size = nums.size();//nums[0...k) store appear once element
        for(int i = 1; i < size; ++i)
        {
            if(nums[i] != nums[i-1])
            {
                if(i != k)
                    nums[k++] = nums[i];
                else
                    ++k;
            }
        }
        return k;
    }
};
```

**Solution 2:**

```c++
class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        int size = nums.size();
        if(size == 0 || size == 1) return size;
        int count = 0;
        for(int i = 1; i < size; ++i)
        {
            if(nums[i] == nums[i-1])
                ++count;
            if(count)
                nums[i-count] = nums[i];
        }
        return size-count;
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
        int k = 0, size = nums.size();//[0, k)
        for (int i = 0; i < size; ++i)
        {
            if(nums[i] != val)
            {
                if(i != k)
                    nums[k++] = nums[i];//swap(nums[i], nums[k++]); //doesn't matter what left in new length
                else
                    ++k;//consider case that all elements in nums are not val
            }
        }
        return k;
    }
};
```

**Solution 3:** order

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

## 75. Sort Colors

Medium

Given an array with *n* objects colored red, white or blue, sort them **[in-place](https://en.wikipedia.org/wiki/In-place_algorithm)** so that objects of the same color are adjacent, with the colors in the order red, white and blue.

Here, we will use the integers 0, 1, and 2 to represent the color red, white, and blue respectively.

**Note:** You are not suppose to use the library's sort function for this problem.

**Example:**

```
Input: [2,0,2,1,1,0]
Output: [0,0,1,1,2,2]
```

**Follow up:**

- A rather straight forward solution is a two-pass algorithm using counting sort.
  First, iterate the array counting number of 0's, 1's, and 2's, then overwrite array with total number of 0's, then 1's and followed by 2's.
- Could you come up with a one-pass algorithm using only constant space?

**Solution: **

```c++
class Solution {
public:
    void sortColors(vector<int>& nums) {        
        //nums[0...zeros] == 0, nums[twos...n-1] == 2, nums[zeros+1...i-1] == 1
        int zeros = -1, twos = nums.size();
        for(int i = 0; i < twos;)
        {
            if(nums[i] == 1)
                ++i;
            else if(nums[i] == 2)
                swap(nums[--twos], nums[i]);
            else
                swap(nums[++zeros], nums[i++]);
        }
        return;
    }
};
```



## 80. Remove Duplicates from Sorted Array II

Medium

Given a sorted array *nums*, remove the duplicates [**in-place**](https://en.wikipedia.org/wiki/In-place_algorithm) such that duplicates appeared at most *twice* and return the new length.

Do not allocate extra space for another array, you must do this by **modifying the input array [in-place](https://en.wikipedia.org/wiki/In-place_algorithm)** with O(1) extra memory.

**Example 1:**

```
Given nums = [1,1,1,2,2,3],

Your function should return length = 5, with the first five elements of nums being 1, 1, 2, 2 and 3 respectively.

It doesn't matter what you leave beyond the returned length.
```

**Example 2:**

```
Given nums = [0,0,1,1,1,1,2,3,3],

Your function should return length = 7, with the first seven elements of nums being modified to 0, 0, 1, 1, 2, 3 and 3 respectively.

It doesn't matter what values are set beyond the returned length.
```

**Clarification:**

Confused why the returned value is an integer but your answer is an array?

Note that the input array is passed in by **reference**, which means modification to the input array will be known to the caller as well.

Internally you can think of this:

```
// nums is passed in by reference. (i.e., without making a copy)
int len = removeDuplicates(nums);

// any modification to nums in your function would be known by the caller.
// using the length returned by your function, it prints the first len elements.
for (int i = 0; i < len; i++) {
    print(nums[i]);
}
```

**Solution 1:** based on 26. Remove Duplicates from Sorted Array.

```c++
class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        if(nums.empty()) return 0;
        int k = 1, size = nums.size();//nums[0...k) store elements that appear at most twice
        int times = 1; //nums[0] once
        for(int i = 1; i < size; ++i)
        {
            if(nums[i] != nums[i-1])
            {
                times = 1;
                nums[k++] = nums[i];
            }
            else
            {
                if(times < 2)
                {
                    nums[k++] = nums[i];
                    ++times;
                }
            }
        }
        return k;
    }
};
```

**Solution 2:** based on 26. Remove Duplicates from Sorted Array.

```
class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        if(nums.empty()) return 0;
        int count = 0, size = nums.size();//count means elements duplicate more than twice numbers
        int times = 1; //nums[0] once
        for(int i = 1; i < size; ++i)
        {
            if(nums[i] != nums[i-1])
            {
                times = 1;                
                nums[i-count] = nums[i];
            }
            else
            {                
                if(times < 2)
                {
                    nums[i-count] = nums[i];
                    ++times;
                }
                else
                    ++count;
            }
        }
        return size-count;
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

**Solution:** 

```c++
class Solution {
public:
void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        int i = m - 1, j = n - 1, tar = m + n - 1;
        while (j >= 0) {
            nums1[tar--] = i >= 0 && nums1[i] > nums2[j] ? nums1[i--] : nums2[j--];
    }
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



## 167. Two Sum II - Input array is sorted

Easy

Given an array of integers that is already **sorted in ascending order**, find two numbers such that they add up to a specific target number.

The function twoSum should return indices of the two numbers such that they add up to the target, where index1 must be less than index2.

**Note:**

- Your returned answers (both index1 and index2) are not zero-based.
- You may assume that each input would have *exactly* one solution and you may not use the *same* element twice.

**Example:**

```
Input: numbers = [2,7,11,15], target = 9
Output: [1,2]
Explanation: The sum of 2 and 7 is 9. Therefore index1 = 1, index2 = 2.
```

**Solution 1:** binary search

```c++
class Solution {
public:
    vector<int> twoSum(vector<int>& numbers, int target) {        
        vector<int> res;
        auto ibegin = numbers.begin(), iend = numbers.end();
        int size = numbers.size();
        for (int i = 0; i < size; ++i)
        {
            if (numbers[i] > target/2)//optimized to exit
                break;
            if (std::binary_search(ibegin, iend, target-numbers[i]))
            {
                auto itarget = std::upper_bound(ibegin, iend, target-numbers[i]);//upper_bound avoid case [0,0,1,2] target 0, lower_bound find the first 0 twice
                res.push_back(i+1);//not zero-based, plus 1
                res.push_back(itarget-1-ibegin+1);
                break;
            }
        }
        return res;
    }
};
```

**Solution 2:** two pointers

```c++
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {        
        vector<int> res;
        int left = 0, right = nums.size()-1;        
        while(left < right)
        {
            if(nums[left] + nums[right] == target)
            {
                res.push_back(left+1);
                res.push_back(right+1);
                break;                
            }
            else if (nums[left] + nums[right] < target)
                ++left;
            else //nums[left] + nums[right] > target
                --right;
        }
        return res;
    }
};
```

## 209. Minimum Size Subarray Sum

Medium

Given an array of **n** positive integers and a positive integer **s**, find the minimal length of a **contiguous** subarray of which the sum ≥ **s**. If there isn't one, return 0 instead.

**Example:** 

```
Input: s = 7, nums = [2,3,1,2,4,3]
Output: 2
Explanation: the subarray [4,3] has the minimal length under the problem constraint.
```

**Follow up:**

If you have figured out the *O*(*n*) solution, try coding another solution of which the time complexity is *O*(*n* log *n*). 

**Solution:** O(n) time.

```c++
class Solution {
public:
    int minSubArrayLen(int s, vector<int>& nums) {
        int size = nums.size();
        int sum = 0, length = size+1;
        //nums[i...j] store sum>=s
        int i = 0, j = -1;
        while(i < size)
        {
            if(j+1 < size && sum < s)
                sum += nums[++j];
            else//j+1 >= size || sum >= s
                sum -= nums[i++];
            if(sum >= s)
                length = min(length, j-i+1);
        }
        if(length == size+1)
            return 0;
        return length;
    }
};
```



## 215. Kth Largest Element in an Array

Medium

Find the **k**th largest element in an unsorted array. Note that it is the kth largest element in the sorted order, not the kth distinct element.

**Example 1:**

```
Input: [3,2,1,5,6,4] and k = 2
Output: 5
```

**Example 2:**

```
Input: [3,2,3,1,2,4,5,5,6] and k = 4
Output: 4
```

**Note:**
You may assume k is always valid, 1 ≤ k ≤ array's length.

**Solution:** 

```c++
class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        int n = nums.size();
        int index = 0, start = 0, end = n-1;
        while(true)
        {
            //the k'th largest index is n-1-(k-1) = n-k
            index = Partition(nums, start, end);
            /*for(auto num: nums)
                cout<<num<<" ";
                */
            //cout<<endl;
            if(index == n-k)
                break;
            else if(index < n-k)
                start = index + 1;
            else//if(index > n-k)
                end = index - 1;            
        }
        return nums[index];
    }
private:
    int Partition(vector<int>& nums, int start, int end)
    {
        if(start == end) return start;
        //nums[start...small] < pivot && nums[big...end] >= pivot, nums[big-1] is pivot
        int pivot = nums[start];
        int small = start-1, big = end+1;
        int i = start+1;
        while(i < big)
        {
            if(nums[i] < pivot)
                nums[++small] = nums[i++];
            else
                swap(nums[--big], nums[i]);
        }
        nums[big-1] = pivot;
        return big-1;
    }
};
```

**Improve :**

```c++
    int Partition(vector<int>& nums, int left, int right)
    {
        int pivot = nums[left], l = left, r = right;
        while(l <= r)
        {
            if(nums[l] > pivot && nums[r] < pivot)
                swap(nums[l++], nums[r--]);
            else if(nums[l] <= pivot)
                ++l;
            else//nums[r] >= pivot
                --r;
        }
        swap(nums[r], nums[left]);
        return r;
    }

    int Partition(vector<int>& nums, int l, int r) {	
	int v = nums[l];
	// arr[l+1...i) <= v; arr(j...r] >= v
	int i = l + 1, j = r;
	while (true) {
		while (i <= r && nums[i] < v)
			i++;
		while (j >= l + 1 && nums[j] > v)
			j--;
		// 对于上面的两个边界的设定, 有的同学在课程的问答区有很好的回答:)
		// 大家可以参考: http://coding.imooc.com/learn/questiondetail/4920.html
		if (i > j)
            break;
		swap(nums[i++], nums[j--]);
	}
	swap(nums[l], nums[j]);
	return j;
}
```



## 242. Valid Anagram

Easy

Given two strings *s* and *t* , write a function to determine if *t* is an anagram of *s*.

**Example 1:**

```
Input: s = "anagram", t = "nagaram"
Output: true
```

**Example 2:**

```
Input: s = "rat", t = "car"
Output: false
```

**Note:**
You may assume the string contains only lowercase alphabets.

**Follow up:**
What if the inputs contain unicode characters? How would you adapt your solution to such case?

**Solution:**

```c++
class Solution {
public:
    bool isAnagram(string s, string t) {
        //space O(1), time O(n+m)
        if(s.empty() && t.empty()) return true;
        int sizeS = s.size(), sizeT = t.size();
        if(sizeS != sizeT) return false;        
        int times[256] = {0};
        for(int i = 0; i < sizeS; ++i)
            ++times[s[i]];
        for(int i = 0; i < sizeT; ++i)
        {
            if(--times[t[i]] < 0)
                return false;
        }
        return true;
    }
};
```

**Improve:**

```c++
class Solution {
public:
    bool isAnagram(string s, string t) {
        //space O(1), time O(n)
        if(s.empty() && t.empty()) return true;
        int sizeS = s.size(), sizeT = t.size();
        if(sizeS != sizeT) return false;        
        int times[256] = {0};
        for(int i = 0; i < sizeS; ++i)
        {
            ++times[s[i]];
            --times[t[i]];
        }
        for(int i = 0; i < sizeT; ++i)
        {
            if(times[t[i]] < 0)
                return false;
        }
        return true;
    }
};
```

**Follow up:**

```
array size from ASCII 256 to Unicode xxx, add memory.
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

**Solution :**

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

**Improve 1:**

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

**Improve 2:**

```c++
class Solution {
public:
    void moveZeroes(vector<int>& nums) {
        int zeroStart = 0, size = nums.size();//[0, zeroStart) [zeroStart,size)
        for (int i = 0; i < size; ++i)
        {
            if(nums[i])
            {
                if(i != zeroStart)
                    swap(nums[i], nums[zeroStart++]);
                else
                    ++zeroStart;
            }
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



## 142. Linked List Cycle II

Medium

Given a linked list, return the node where the cycle begins. If there is no cycle, return `null`.

To represent a cycle in the given linked list, we use an integer `pos` which represents the position (0-indexed) in the linked list where tail connects to. If `pos` is `-1`, then there is no cycle in the linked list.

**Note:** Do not modify the linked list.

 

**Example 1:**

```
Input: head = [3,2,0,-4], pos = 1
Output: tail connects to node index 1
Explanation: There is a cycle in the linked list, where tail connects to the second node.
```

![img](https://assets.leetcode.com/uploads/2018/12/07/circularlinkedlist.png)

**Example 2:**

```
Input: head = [1,2], pos = 0
Output: tail connects to node index 0
Explanation: There is a cycle in the linked list, where tail connects to the first node.
```

![img](https://assets.leetcode.com/uploads/2018/12/07/circularlinkedlist_test2.png)

**Example 3:**

```
Input: head = [1], pos = -1
Output: no cycle
Explanation: There is no cycle in the linked list.
```

![img](https://assets.leetcode.com/uploads/2018/12/07/circularlinkedlist_test3.png)

 

**Follow-up**:
Can you solve it without using extra space?

**Solution 1:** normal find use 141 solution, have math prove.

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
    ListNode *detectCycle(ListNode *head) {
        ListNode* dummyHead = new ListNode(-1);
        dummyHead->next = head;
        ListNode* fast, *slow;
        fast = slow = dummyHead;
        while (fast && fast->next)
        {
            slow = slow->next;
            fast = fast->next->next;
            if (slow == fast)
                break;
        }
        if(!fast || !fast->next)//no cycle
            return NULL;
        slow = dummyHead;//reset
        while(slow != fast)
        {
            slow = slow->next;
            fast = fast->next;
        }
        return slow;
    }
};
```

**Solution 2:** Improved solution 1 in condition if find cycle.

```c++
class Solution {
public:
    ListNode *detectCycle(ListNode *head) {
        ListNode* dummyHead = new ListNode(-1);
        dummyHead->next = head;
        ListNode* fast, *slow, *entry;
        fast = slow = entry = dummyHead;
        while (fast && fast->next)
        {
            slow = slow->next;
            fast = fast->next->next;
            if (slow == fast)
            {
                while(slow != entry)
                {
                    slow = slow->next;
                    entry = entry->next;
                }
                return entry;
            }
        }
        return NULL;
    }
};
```

**Solution 3:** no dummy head.

```c++
class Solution {
public:
    ListNode *detectCycle(ListNode *head) {
        if (!head || !head->next)
            return NULL;

        ListNode *slow  = head;
        ListNode *fast  = head;
        ListNode *entry = head;

        while (fast->next && fast->next->next) {
            slow = slow->next;
            fast = fast->next->next;
            if (slow == fast) {                      // there is a cycle
                while(slow != entry) {               // found the entry location
                    slow  = slow->next;
                    entry = entry->next;
                }
                return entry;
            }
        }
        return NULL;                                 // there has no cycle
    }
};
```



## 206. Reverse Linked List

Easy

Reverse a singly linked list.

**Example:**

```
Input: 1->2->3->4->5->NULL
Output: 5->4->3->2->1->NULL
```

**Follow up:**

A linked list can be reversed either iteratively or recursively. Could you implement both?

**Solution:** iteratively. 

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
    ListNode* reverseList(ListNode* head) {
        ListNode* pre= NULL;
        ListNode* cur = head;
        while(cur)
        {
            ListNode* next = cur->next;
            cur->next = pre;
            pre = cur;
            cur = next;
        }
        return pre;
    }
};
```

**Follow up:** recursively. 

```c++
class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        if(!head) return NULL;
        ListNode* newHead = NULL;
        ListNode* newTail = Recursive(head, newHead);
        newTail->next = NULL;//remeber!!!
        return newHead;
    }
private:
    //Recursive函数将原链表的cur节点及后续节点反序
    //返回新链表的尾结点，传入引用作为新头结点
    ListNode* Recursive(ListNode* cur, ListNode* &newHead)
    {
        if(cur->next == NULL)
        {
            newHead = cur;
        }
        else
        {
            ListNode* newTail = Recursive(cur->next, newHead);
            newTail->next = cur;
        }
        return cur;
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



## 76. Minimum Window Substring

Hard

Given a string S and a string T, find the minimum window in S which will contain all the characters in T in complexity O(n).

**Example:**

```
Input: S = "ADOBECODEBANC", T = "ABC"
Output: "BANC"
```

**Note:**

- If there is no such window in S that covers all characters in T, return the empty string `""`.
- If there is such window, you are guaranteed that there will always be only one unique minimum window in S.

**Solution:** 

```c++
class Solution {
public:
    string minWindow(string s, string t) {
        int sizeS = s.size(), sizeT = t.size();
        string res;
        if(s.empty() || t.empty() || sizeS < sizeT)
            return res;
        vector<int> freq(256, 0);//ascii
        for(int i = 0; i < sizeT; ++i)
            ++freq[t[i]];
        int count = sizeT;
        //s[l...r] store window
        int l = 0, r = -1;
        int minLength = sizeS+1;// minLength > sizeS
        while(l <= sizeS-sizeT)
        {
            //cout<<"l="<<l<<" r="<<r<<endl;
            if(count == 0)
            {
                if(r-l+1 < minLength)
                {
                    res = s.substr(l,r-l+1);
                    minLength = r-l+1;
                    //cout<<"res = "<<res<<endl;
                }                
                if(freq[s[l++]]++ >= 0)
                    ++count;
            }
            else
            {
                if(r+1 < sizeS && freq[s[++r]]-- >= 1)
                    --count;
                else if(r+1 >= sizeS)//when r index is sizeS-1 and count != 0, dead while condition! need ++l!
                    ++l;
            }
        }
        return res;
    }
};
```

**Improve:**



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



## 344. Reverse String

Easy

Write a function that reverses a string. The input string is given as an array of characters `char[]`.

Do not allocate extra space for another array, you must do this by **modifying the input array [in-place](https://en.wikipedia.org/wiki/In-place_algorithm)** with O(1) extra memory.

You may assume all the characters consist of [printable ascii characters](https://en.wikipedia.org/wiki/ASCII#Printable_characters).

 

**Example 1:**

```
Input: ["h","e","l","l","o"]
Output: ["o","l","l","e","h"]
```

**Example 2:**

```
Input: ["H","a","n","n","a","h"]
Output: ["h","a","n","n","a","H"]
```

**Solution:**

```c++
class Solution {
public:
    void reverseString(vector<char>& s) {
        int i = 0, j = s.size()-1;//two pointers
        while(i < j)
            swap(s[i++], s[j--]);
    }
};

class Solution {
public:
    void reverseString(vector<char>& s) {
        int i = 0, size = s.size(), halfSize = size/2, end = size-1;
        while(i < halfSize)//one pointer
        {            
            swap(s[i++], s[end-i]);
        }
    }
};
```



## 345. Reverse Vowels of a String

Easy

Write a function that takes a string as input and reverse only the vowels of a string.

**Example 1:**

```
Input: "hello"
Output: "holle"
```

**Example 2:**

```
Input: "leetcode"
Output: "leotcede"
```

**Note:**
The vowels does not include the letter "y".

**Solution:**

```c++
class Solution {
public:
    string reverseVowels(string s) {
        int i = 0, j = s.size()-1;
        while(i < j)
        {
            if(IsVowels(s[i]) && IsVowels(s[j]))
            {
                swap(s[i++], s[j--]);
                continue;
            }                
            if(!IsVowels(s[i]))
                ++i;
            if(!IsVowels(s[j]))
                --j;
        }
        return s;
    }
private:
    bool IsVowels(char c)
    {
        return c=='a' || c=='A'
            || c=='e' || c=='E'
            || c=='i' || c=='I' 
            || c=='o' || c=='O' 
            || c=='u' || c=='U' ;
    }
};
```

**Improve:** 

```c++
class Solution {
public:
    string reverseVowels(string s) {
        int i = 0, j = s.size() - 1;
        while (i < j) {
            i = s.find_first_of("aeiouAEIOU", i);
            j = s.find_last_of("aeiouAEIOU", j);
            if (i < j) {
                swap(s[i++], s[j--]);
            }
        }
        return s;
    }
};
```



## 438. Find All Anagrams in a String

Medium

Given a string **s** and a **non-empty** string **p**, find all the start indices of **p**'s anagrams in **s**.

Strings consists of lowercase English letters only and the length of both strings **s** and **p** will not be larger than 20,100.

The order of output does not matter.

**Example 1:**

```
Input:
s: "cbaebabacd" p: "abc"

Output:
[0, 6]

Explanation:
The substring with start index = 0 is "cba", which is an anagram of "abc".
The substring with start index = 6 is "bac", which is an anagram of "abc".
```



**Example 2:**

```
Input:
s: "abab" p: "ab"

Output:
[0, 1, 2]

Explanation:
The substring with start index = 0 is "ab", which is an anagram of "ab".
The substring with start index = 1 is "ba", which is an anagram of "ab".
The substring with start index = 2 is "ab", which is an anagram of "ab".
```

**Solution:**

```c++
class Solution {
public:
    vector<int> findAnagrams(string s, string p) {        
        int sizeS = s.size(), sizeP = p.size();
        vector<int> res;
        if(s.empty() || p.empty() || sizeS < sizeP)
            return res;
        //s[l...r] store window
        int l = 0, r = -1;
        vector<int> freq(26, 0);//a-z
        while(l <= sizeS-sizeP)
        {
            //keep window length sizeP
            if(r-l+1 < sizeP)
                ++freq[s[++r]-'a'];
            else//r-l+1 == sizeP
            {
                //p in s[l...r]
                if(Anagram(p, freq))
                    res.push_back(l);
                --freq[s[l++]-'a'];
            }                
        }
        return res;
    }
private:
    bool Anagram(const string& p, vector<int> freq)
    {
        int size = p.size();
        for(int i = 0; i < size; ++i)
            --freq[p[i]-'a'];
        for(int i = 0; i < size; ++i)
        {
            if(freq[p[i]-'a'] != 0)
                return false;
        }
        return true;
    }
};
```

**Improve 1:**

```c++
class Solution {
public:
    vector<int> findAnagrams(string s, string p) {        
        int sizeS = s.size(), sizeP = p.size();
        vector<int> res;
        if(s.empty() || p.empty() || sizeS < sizeP)
            return res;
        freq.resize(26, 0);
        for(int i = 0; i < sizeP; ++i)
            ++freq[p[i]-'a'];
        
        //s[l...r] store window
        int l = 0, r = -1;        
        while(l <= sizeS-sizeP)
        {
            //keep window length sizeP
            if(r-l+1 < sizeP)
                --freq[s[++r]-'a'];
            else//r-l+1 == sizeP
            {
                //p in s[l...r]
                if(Anagram(p, sizeP))
                    res.push_back(l);
                ++freq[s[l++]-'a'];
            }                
        }
        return res;
    }
private:
    vector<int> freq;//a-z    
    bool Anagram(const string& p, int size)
    {
        for(int i = 0; i < size; ++i)
        {
            if(freq[p[i]-'a'] != 0)
                return false;
        }
        return true;
    }
};
```

**Improve 2:**

```c++
class Solution {
public:
    vector<int> findAnagrams(string s, string p) {        
        int sizeS = s.size(), sizeP = p.size();
        vector<int> res;
        if(s.empty() || p.empty() || sizeS < sizeP)
            return res;
        freq.resize(26, 0);
        for(int i = 0; i < sizeP; ++i)
            ++freq[p[i]-'a'];
        int count = sizeP;
        //s[l...r] store window
        int l = 0, r = -1;        
        while(l <= sizeS-sizeP)
        {
            //keep window length sizeP
            if(r-l+1 < sizeP)
            {
                if(freq[s[++r]-'a']-- >= 1)
                    --count;
            }
            else//r-l+1 == sizeP
            {
                //p in s[l...r]
                if(count == 0)
                    res.push_back(l);
                if(freq[s[l++]-'a']++ >= 0)//cuz if c not in string t but appear in string s, freq[c] < 0
                    ++count;
            } 
        }
        return res;
    }
private:
    vector<int> freq;//a-z    
};

//循环内容另一种思路
        while(l <= sizeS-sizeP)
        {
            //keep window length sizeP
            if(freq[s[++r]-'a']-- >= 1)
                --count;
            //p in s[l...r]
            if(count == 0)
                res.push_back(l);
            if(r-l+1 == sizeP && freq[s[l++]-'a']++ >= 0)
                ++count;
        }
```

**Improve 3:** template solution for Sliding-Window-Algorithm!

 https://leetcode.com/problems/find-all-anagrams-in-a-string/discuss/92007/Sliding-Window-algorithm-template-to-solve-all-the-Leetcode-substring-search-problem. 



# Map/Set/Hash Table

## 15. 3Sum

Medium

Given an array `nums` of *n* integers, are there elements *a*, *b*, *c* in `nums` such that *a* + *b* + *c* = 0? Find all unique triplets in the array which gives the sum of zero.

**Note:**

The solution set must not contain duplicate triplets.

**Example:**

```
Given array nums = [-1, 0, 1, 2, -1, -4],

A solution set is:
[
  [-1, 0, 1],
  [-1, -1, 2]
]
```

**Solution:**

```c++
class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int>> result;
        if(nums.empty()) return result;
        sort(nums.begin(), nums.end());
        for(int i = 0; i < nums.size(); ++i)
        {
            //if(i > 0 && nums[i] == nums[i-1]) continue;//unique
            int target = 0 - nums[i];
            int front = i + 1, end = nums.size()-1;
            //cout<<"i="<<i<<endl;
            while(front < end)
            {
                int sum = nums[front] + nums[end];
                if(sum == target)
                {
                    vector<int> triplets;
                    triplets.push_back(nums[i]);
                    triplets.push_back(nums[front++]);
                    triplets.push_back(nums[end--]);
                    result.push_back(triplets);
                    while(front < end && nums[front] == triplets[1])
                        ++front;
                    while(front < end && nums[end] == triplets[2])
                        --end;
                }
                else if (sum < target)
                {
                    ++front;
                }
                else// sum > target
                {
                    --end;
                }
               //cout<<"front="<<front<<" end="<<end<<endl;
            }
            while(i+1 < nums.size() && nums[i+1] == nums[i])
                ++i;
        }
        return result;
    }
};
```



## 18. 4Sum

Medium

Given an array `nums` of *n* integers and an integer `target`, are there elements *a*, *b*, *c*, and *d* in `nums` such that *a* + *b* + *c* + *d* = `target`? Find all unique quadruplets in the array which gives the sum of `target`.

**Note:**

The solution set must not contain duplicate quadruplets.

**Example:**

```
Given array nums = [1, 0, -1, 0, -2, 2], and target = 0.

A solution set is:
[
  [-1,  0, 0, 1],
  [-2, -1, 1, 2],
  [-2,  0, 0, 2]
]
```

**Solution:**

```c++
class Solution {
public:
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        vector<vector<int>> result;
        if(nums.empty()) return result;
        sort(nums.begin(), nums.end());
        for(int i = 0; i < nums.size(); ++i)
        {
            for(int j = i+1; j < nums.size(); ++j)
            {
                int targetLeft = target - nums[i] - nums[j];
                int front = j + 1, end = nums.size()-1;
                while(front < end)
                {
                    int sum = nums[front] + nums[end];
                    if(sum == targetLeft)
                    {
                        vector<int> quadruplets;
                        quadruplets.push_back(nums[i]);
                        quadruplets.push_back(nums[j]);
                        quadruplets.push_back(nums[front++]);
                        quadruplets.push_back(nums[end--]);
                        result.push_back(quadruplets);
                        while(front < end && nums[front] == quadruplets[2])
                            ++front;
                        while(front < end && nums[end] == quadruplets[3])
                            --end;
                    }
                    else if (sum < targetLeft)
                    {
                        ++front;
                    }
                    else// sum > targetLeft
                    {
                        --end;
                    }
                }
                while(j+1 < nums.size() && nums[j+1] == nums[j])
                {
                    ++j;//unique
                }
            }
            while(i+1 < nums.size() && nums[i+1] == nums[i])
            {
                ++i;//unique
            }            
        }
        return result;
    }
};

class Solution {
public:
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        vector<vector<int>> result;
        if(nums.empty()) return result;
        sort(nums.begin(), nums.end());
        for(int i = 0; i < nums.size(); ++i)
        {
            if(i > 0 && nums[i-1] == nums[i]) continue;
            for(int j = i+1; j < nums.size(); ++j)
            {
                if(j > i+1 && nums[j-1] == nums[j]) continue;
                int targetLeft = target - nums[i] - nums[j];
                int front = j + 1, end = nums.size()-1;
                while(front < end)
                {
                    int sum = nums[front] + nums[end];
                    if(sum == targetLeft)
                    {
                        vector<int> quadruplets;
                        quadruplets.push_back(nums[i]);
                        quadruplets.push_back(nums[j]);
                        quadruplets.push_back(nums[front++]);
                        quadruplets.push_back(nums[end--]);
                        result.push_back(quadruplets);
                        while(front < end && nums[front] == quadruplets[2])
                            ++front;
                        while(front < end && nums[end] == quadruplets[3])
                            --end;
                    }
                    else if (sum < targetLeft)
                    {
                        ++front;
                    }
                    else// sum > targetLeft
                    {
                        --end;
                    }
                }
            }         
        }
        return result;
    }
};
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

**Solution:**

```c++
class Solution {
public:
    bool isHappy(int n) {
        int result = n;
        unordered_set<int> record;
        while(result != 1)
        {
            record.insert(result);
            result = CalSquareOfDigits(result);
            if(record.find(result) != record.end())
                return false;
        }
        return true;
    }
private:
    int CalSquareOfDigits(int number)
    {
        int result = 0;
        while(number)
        {
            int digit = number%10;
            number/=10;
            result += digit*digit;
        }
        return result;
    }
};
```



## 205. Isomorphic Strings

Easy

Given two strings ***s\*** and ***t\***, determine if they are isomorphic.

Two strings are isomorphic if the characters in ***s\*** can be replaced to get ***t\***.

All occurrences of a character must be replaced with another character while preserving the order of characters. No two characters may map to the same character but a character may map to itself.

**Example 1:**

```
Input: s = "egg", t = "add"
Output: true
```

**Example 2:**

```
Input: s = "foo", t = "bar"
Output: false
```

**Example 3:**

```
Input: s = "paper", t = "title"
Output: true
```

**Note:**
You may assume both ***s\*** and ***t\*** have the same length.

**Solution:** 

```c++
class Solution {
public:
    bool isIsomorphic(string s, string t) {              
        if(s.empty()) return true;
        //size m = n, space O(n), time O(n)
        unordered_map<char, char> s2t;
        unordered_map<char, char> t2s;
        for(int i = 0; i < s.size(); ++i)
        {
            if(s2t.find(s[i]) != s2t.end())
            {
                if(s2t[s[i]] != t[i])
                    return false;
            }
            else
                    s2t[s[i]] = t[i];
            
            if(t2s.find(t[i]) != t2s.end())
            {
                if(t2s[t[i]] != s[i])
                    return false;
            }
            else
                    t2s[t[i]] = s[i];
                        
        }
        return true;
    }
};

class Solution {
public:
    bool isIsomorphic(string s, string t) {              
        if(s.empty()) return true;
        //size m = n, space O(n), time O(n)
        unordered_map<char, char> s2t;
        unordered_map<char, char> t2s;
        for(int i = 0; i < s.size(); ++i)
        {
            if(s2t[s[i]] == 0 && t2s[t[i]] == 0)
            {
                s2t[s[i]] = t[i];
                t2s[t[i]] = s[i];
                continue;
            }            
            if(s2t[s[i]] != t[i])//default mapping is ch->0
                return false;
        }
        return true;
    }
};
```



## 290. Word Pattern

Easy

Given a `pattern` and a string `str`, find if `str` follows the same pattern.

Here **follow** means a full match, such that there is a bijection between a letter in `pattern` and a **non-empty** word in `str`.

**Example 1:**

```
Input: pattern = "abba", str = "dog cat cat dog"
Output: true
```

**Example 2:**

```
Input:pattern = "abba", str = "dog cat cat fish"
Output: false
```

**Example 3:**

```
Input: pattern = "aaaa", str = "dog cat cat dog"
Output: false
```

**Example 4:**

```
Input: pattern = "abba", str = "dog dog dog dog"
Output: false
```

**Notes:**
You may assume `pattern` contains only lowercase letters, and `str` contains lowercase letters that may be separated by a single space.

**Solution:**

```c++
class Solution {
public:
    bool wordPattern(string pattern, string str) {
        if(pattern.empty() || str.empty()) return pattern.empty() && str.empty();
        //size m = n, space O(n), time O(n)
        unordered_map<char, string> c2s;
        unordered_map<string, char> s2c;
        string singleSpace = " ";
        size_t pos = 0;
        
        for(int i = 0; i < pattern.size(); ++i)
        {
            if(pos == str.size()+1) return false;
            size_t begin = pos;
            pos = str.find_first_of(singleSpace, begin);
            if(pos == -1) //pos= npos, substr [begin, pos) return [begin, size())
                pos = str.size();
            auto nextStr = str.substr(begin, pos-begin);//find next string in str, separeted by single space
            ++pos;//next string in str!!!
            cout<<"char[i]="<<pattern[i]<<"  nextStr="<<nextStr<<endl;
            if(c2s[pattern[i]] == "" && s2c[nextStr] == 0)
            {
                c2s[pattern[i]] = nextStr;
                s2c[nextStr] = pattern[i];
                continue;
            }            
            if(c2s[pattern[i]] != nextStr)//default mapping is string->""
                return false;
        }
        return pos == str.size() + 1;
    }
};
```

```c++
class Solution {
public:
    bool wordPattern(string pattern, string str) {
        
        stringstream ss(str);  // 字符流ss 
        string buf;
        vector<string> tokens;
        while (ss >> buf)  
            tokens.push_back(buf);
        if(pattern.size() != tokens.size())
            return false;
        
        map<string, char> s2c;
        map<char, string> c2s;
        for (int i = 0; i < tokens.size(); ++i) 
        {
            if (s2c[tokens[i]] == 0 && c2s[pattern[i]] == "") 
            {
                    s2c[tokens[i]] = pattern[i];
                    c2s[pattern[i]] = tokens[i];
                    continue;
            }
            if (s2c[tokens[i]] != pattern[i]) return false;
        }
        return true;
}
    
};
```



## 349. Intersection of Two Arrays

Easy

Given two arrays, write a function to compute their intersection.

**Example 1:**

```
Input: nums1 = [1,2,2,1], nums2 = [2,2]
Output: [2]
```

**Example 2:**

```
Input: nums1 = [4,9,5], nums2 = [9,4,9,8,4]
Output: [9,4]
```

**Note:**

- Each element in the result must be unique.
- The result can be in any order.

**Solution:**

```c++
class Solution {
public:
    vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
        //space O(n), time O(n+m)
        unordered_set<int> record(nums1.begin(), nums1.end());
        unordered_set<int> result;
        for(auto num: nums2)
        {
            if(record.find(num) != record.end())
                result.insert(num);
        }
        vector<int> res(result.begin(), result.end());
        return res;
    }
};
```

**Improve:**

```c++
class Solution {
public:
    vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
        //space O(n+m), time O(min(n,m))
        unordered_set<int> record1(nums1.begin(), nums1.end());
        unordered_set<int> record2(nums2.begin(), nums2.end());
        int size1 = record1.size(), size2 = record2.size();
        if(size1 > size2)
            swap(record1, record2);
        
        vector<int> result;
        for(auto num: record1)
        {
            if(record2.find(num) != record2.end())
                result.push_back(num);
        }
        return result;
    }
};
```

```c++
class Solution {
public:
    vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
        //space O(min(n,m)), time O(n+m)
        int size1 = nums1.size(), size2 = nums2.size();
        unordered_set<int> record;
        if(size1 < size2)//not precise compare cuz may repeate
            swap(nums1, nums2);
        record.insert(nums2.begin(), nums2.end());
        
        unordered_set<int> result;
        for(auto num: nums1)
        {
            if(record.find(num) != record.end())
                result.insert(num);
        }
        vector<int> res(result.begin(), result.end());
        return res;
    }
};
```



## 350. Intersection of Two Arrays II

Easy

Given two arrays, write a function to compute their intersection.

**Example 1:**

```
Input: nums1 = [1,2,2,1], nums2 = [2,2]
Output: [2,2]
```

**Example 2:**

```
Input: nums1 = [4,9,5], nums2 = [9,4,9,8,4]
Output: [4,9]
```

**Note:**

- Each element in the result should appear as many times as it shows in both arrays.
- The result can be in any order.

**Follow up:**

- What if the given array is already sorted? How would you optimize your algorithm?
- What if *nums1*'s size is small compared to *nums2*'s size? Which algorithm is better?
- What if elements of *nums2* are stored on disk, and the memory is limited such that you cannot load all elements into the memory at once?

**Solution:**

```c++
class Solution {
public:
    vector<int> intersect(vector<int>& nums1, vector<int>& nums2) {
        //space O(n), time O(n+m)
        unordered_map<int/* number */, int/*count*/> record;
        for(auto num: nums1)
            ++record[num];
        vector<int> result;
        for(auto num: nums2)
            if(record[num]-- > 0)
                result.push_back(num);
        return result;
    }
};
```

**Improve:**

```c++
class Solution {
public:
    vector<int> intersect(vector<int>& nums1, vector<int>& nums2) {
        //space O(min(n,m)), time O(n+m)
        if(nums1.size() < nums2.size())
            swap(nums1, nums2);
        unordered_map<int/* number */, int/*count*/> record;
        for(auto num: nums1)
            ++record[num];
        vector<int> result;
        for(auto num: nums2)
            if(record[num]-- > 0)
                result.push_back(num);
        return result;
    }
};
```

**Follow up 1:** two pointers.

```c++
class Solution {
public:
    vector<int> intersect(vector<int>& nums1, vector<int>& nums2) {
        //space O(1), time O(max(nlogn,mlogm)), but this do not need us to do!
        sort(nums1.begin(), nums1.end());
        sort(nums2.begin(), nums2.end());
        
        //space O(min(n,m)), time O(min(n,m))
        int i = 0, size1 = nums1.size();
        int j = 0, size2 = nums2.size();
        vector<int> result;
        while(i < size1 && j < size2)
        {
            if(nums1[i] == nums2[j])
            {
                result.push_back(nums1[i]);
                ++i;++j;
            }
            else if(nums1[i] > nums2[j])
                ++j;
            else
                ++i;
        }
        return result;
    }
};
```

**Follow up 2:**

```
n<m, improve time(m+n), follow up 1 time(n), so follow up 1 is better.
```

**Follow up 3:**

```
nums2 in file.in, load part of elements into memory and use solution.
```



## 451. Sort Characters By Frequency

Medium

Given a string, sort it in decreasing order based on the frequency of characters.

**Example 1:**

```
Input:
"tree"

Output:
"eert"

Explanation:
'e' appears twice while 'r' and 't' both appear once.
So 'e' must appear before both 'r' and 't'. Therefore "eetr" is also a valid answer.
```



**Example 2:**

```
Input:
"cccaaa"

Output:
"cccaaa"

Explanation:
Both 'c' and 'a' appear three times, so "aaaccc" is also a valid answer.
Note that "cacaca" is incorrect, as the same characters must be together.
```



**Example 3:**

```
Input:
"Aabb"

Output:
"bbAa"

Explanation:
"bbaA" is also a valid answer, but "Aabb" is incorrect.
Note that 'A' and 'a' are treated as two different characters.
```

**Solution:**

```c++
class Solution {
public:
    string frequencySort(string s) {
        //space O(n), time O(nlogn)
        unordered_map<char, int> record;
        for(int i = 0; i < s.size(); ++i)
            ++record[s[i]];
        vector< pair<char,int> > vec(record.begin(), record.end());
        sort(vec.begin(), vec.end(), Compare);
        string result;
        for(auto p: vec)
            result.insert(result.end(), p.second, p.first);
        return result;
    }
private:
    static bool Compare(const pair<char,int> &p1, const pair<char,int> &p2)
    {
        return p1.second > p2.second;
    }    
};

```



# Stack

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



## 155. Min Stack

Easy

Design a stack that supports push, pop, top, and retrieving the minimum element in constant time.

- push(x) -- Push element x onto stack.
- pop() -- Removes the element on top of the stack.
- top() -- Get the top element.
- getMin() -- Retrieve the minimum element in the stack.

 

**Example:**

```
MinStack minStack = new MinStack();
minStack.push(-2);
minStack.push(0);
minStack.push(-3);
minStack.getMin();   --> Returns -3.
minStack.pop();
minStack.top();      --> Returns 0.
minStack.getMin();   --> Returns -2.
```

```c++
class MinStack {
public:
    /** initialize your data structure here. */
    MinStack() {
        
    }
    
    void push(int x) {
        data.push(x);
        if(aux.empty())
            aux.push(x);
        else
            aux.push(x<aux.top()?x:aux.top());
    }
    
    void pop() {
        if(data.empty()) throw "data empty!";
        data.pop();
        aux.pop();
    }
    
    int top() {
        if(data.empty()) throw "data empty!";
        return data.top();
    }
    
    int getMin() {
        if(aux.empty()) throw "aux empty!";
        return aux.top();
    }
private:
    stack<int> data;
    stack<int> aux;
};

/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack* obj = new MinStack();
 * obj->push(x);
 * obj->pop();
 * int param_3 = obj->top();
 * int param_4 = obj->getMin();
 */
```



## 844. Backspace String Compare

Easy

Given two strings `S` and `T`, return if they are equal when both are typed into empty text editors. `#` means a backspace character.

**Example 1:**

```
Input: S = "ab#c", T = "ad#c"
Output: true
Explanation: Both S and T become "ac".
```

**Example 2:**

```
Input: S = "ab##", T = "c#d#"
Output: true
Explanation: Both S and T become "".
```

**Example 3:**

```
Input: S = "a##c", T = "#a#c"
Output: true
Explanation: Both S and T become "c".
```

**Example 4:**

```
Input: S = "a#c", T = "b"
Output: false
Explanation: S becomes "c" while T becomes "b".
```

**Note**:

1. `1 <= S.length <= 200`
2. `1 <= T.length <= 200`
3. `S` and `T` only contain lowercase letters and `'#'` characters.

**Follow up:**

- Can you solve it in `O(N)` time and `O(1)` space?

**Solution:** O(M+N) time and O(M+N) space

```c++
class Solution {
public:
    bool backspaceCompare(string S, string T) {
        return buildFinalString(S) == buildFinalString(T);
    }
    string buildFinalString(string str)
    {
        stack<char> stk;
        int size = str.size();
        for(int i = 0; i < size; ++i)
        {
            if(str[i] == '#')
            {
                if(!stk.empty())
                    stk.pop();
            }
            else
                stk.push(str[i]);
        }
        string res;
        while(!stk.empty())
        {
            res.push_back(stk.top());
            stk.pop();
        }
        reverse(res.begin(), res.end());
        return res;
    }
};
```

**Improve: ** two pointers iterate through the string in reverse, O(M+N) time and O(1) space.

```c++
class Solution {
public:
    bool backspaceCompare(string S, string T) {
        int i = S.length() - 1, j = T.length() - 1;
        int skipS = 0, skipT = 0;
        while (i >= 0 || j >= 0) { // While there may be chars in build(S) or build (T)
            while (i >= 0) { // Find position of next possible char in build(S)
                if (S[i] == '#') {++skipS; --i;}
                else if (skipS > 0) {--skipS; --i;}
                else break;
            }
            while (j >= 0) { // Find position of next possible char in build(T)
                if (T[j] == '#') {++skipT; --j;}
                else if (skipT > 0) {--skipT; --j;}
                else break;
            }
            // If two actual characters are different
            if (i >= 0 && j >= 0 && S[i] != T[j])
                return false;
            // If expecting to compare char vs nothing
            if ((i >= 0) != (j >= 0))
                return false;
            --i; --j;
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
            res ^= num;
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

**Solution 1**

```c++
class Solution {
public:
    int titleToNumber(string s) {
        int size = s.size();
        long long res = 0;
        for(int i = 0; i < size; ++i)
        {
            res = 26*res + s[i]-'A'+1;
        }
        return (int)res;
    }
};
```

**Solution 2**

```c++
class Solution {
public:
    int titleToNumber(string s) {
        int col = 0;
        for(int i = s.length(); i > 0; i--) {
            col += (s[i - 1] - 'A' + 1) * pow(26, (s.length() - i));
        }
        return col;
    }
};

```



## 258. Add Digits

Easy

Given a non-negative integer `num`, repeatedly add all its digits until the result has only one digit.

**Example:**

```
Input: 38
Output: 2 
Explanation: The process is like: 3 + 8 = 11, 1 + 1 = 2. 
             Since 2 has only one digit, return it.
```

**Follow up:**
Could you do it without any loop/recursion in O(1) runtime?

**Solution:**

```c++
class Solution {
public:
    int addDigits(int num) {
        int result = num;
        while(result >= 10)
            result = AddDigits(result);
        return result;
    }
private:
    int AddDigits(int number)
    {
        int result = 0;
        while(number)
        {
            int digit = number%10;
            number/=10;
            result += digit;
        }
        return result;
    }    
};
```

**Improve:**

```c++
class Solution {
public:
    int addDigits(int num) {
        return (num-1)%9 + 1;
    }  
};
```



## 263. Ugly Number

Easy

Write a program to check whether a given number is an ugly number.

Ugly numbers are **positive numbers** whose prime factors only include `2, 3, 5`.

**Example 1:**

```
Input: 6
Output: true
Explanation: 6 = 2 × 3
```

**Example 2:**

```
Input: 8
Output: true
Explanation: 8 = 2 × 2 × 2
```

**Example 3:**

```
Input: 14
Output: false 
Explanation: 14 is not ugly since it includes another prime factor 7.
```

**Note:**

1. `1` is typically treated as an ugly number.
2. Input is within the 32-bit signed integer range: [−231, 231 − 1].

**Solution:**

```c++
class Solution {
public:
    bool isUgly(int num) {
        int result = num;
        result = MoveFactor(result, 2);
        result = MoveFactor(result, 3);
        result = MoveFactor(result, 5);        
        return result == 1;
    }
private:
    int MoveFactor(int num, int factor)
    {
        //not check factor
        int result = num;
        while(result != 0 && result % factor == 0)
        {
            result /= factor;
        }
        return result;
    }
};

class Solution {
public:
    bool isUgly(int num) {//判断是否为丑数
        if(num<=0) return false;
        for (int i=2; i<6 && num; i++)
        while (num % i == 0)
            num /= i;
        return num == 1;
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



# Tree

## 100. Same Tree

Easy

Given two binary trees, write a function to check if they are the same or not.

Two binary trees are considered the same if they are structurally identical and the nodes have the same value.

**Example 1:**

```
Input:     1         1
          / \       / \
         2   3     2   3

        [1,2,3],   [1,2,3]

Output: true
```

**Example 2:**

```
Input:     1         1
          /           \
         2             2

        [1,2],     [1,null,2]

Output: false
```

**Example 3:**

```
Input:     1         1
          / \       / \
         2   1     1   2

        [1,2,1],   [1,1,2]

Output: false
```

**Solution:**

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
    bool isSameTree(TreeNode* p, TreeNode* q) {
        if(p && q)
        {
            if(p->val != q->val)
                return false;
            return isSameTree(p->left, q->left) && isSameTree(p->right, q->right);
        }
        return p==q;//p==NULL && q==NULL
    }
};

class Solution {
public:
    bool isSameTree(TreeNode* p, TreeNode* q) {
        if(p==NULL&&q==NULL) return true;
        if(p==NULL) return false;
        if(q==NULL) return false;
        if(p->val!=q->val) return false;
        return isSameTree(p->left,q->left)&&isSameTree(p->right,q->right);
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

**Solution:**

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
        if(root)
            return isSymmetric(root->left, root->right);
        return true;
    }
private:
    bool isSymmetric(TreeNode* r1, TreeNode* r2) {
        if(r1 && r2)
        {
            if(r1->val != r2->val)
                return false;
            return isSymmetric(r1->left, r2->right)
                && isSymmetric(r1->right, r2->left);
        }
        return r1 == r2;//==NULL
    }
};

class Solution {
public:
    bool isSymmetric(TreeNode* root) {
        if(root==NULL) return true;
        return isMirror(root,root);
    }
    bool isMirror(TreeNode* t1,TreeNode* t2){
        if(t1==NULL&&t2==NULL) return true;
        if(t1==NULL||t2==NULL) return false;
        return (t1->val==t2->val)&&isMirror(t1->left,t2->right)&&isMirror(t1->right,t2->left);
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

**Solution:**

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
    int maxDepth(TreeNode* root) {
        if(!root)
            return 0;
        return max(maxDepth(root->left), maxDepth(root->right)) + 1;
    }
};
```



## 110. Balanced Binary Tree

Easy

Given a binary tree, determine if it is height-balanced.

For this problem, a height-balanced binary tree is defined as:

> a binary tree in which the left and right subtrees of *every* node differ in height by no more than 1.

 

**Example 1:**

Given the following tree `[3,9,20,null,null,15,7]`:

```
    3
   / \
  9  20
    /  \
   15   7
```

Return true.

**Example 2:**

Given the following tree `[1,2,2,3,3,null,null,4,4]`:

```
       1
      / \
     2   2
    / \
   3   3
  / \
 4   4
```

Return false.

**Solution:** top-down, time O(nlogn)

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
    bool isBalanced(TreeNode* root) {
        if(!root) return true;
        return abs(maxDepth(root->left)-maxDepth(root->right)) <= 1 
            && isBalanced(root->left)
            && isBalanced(root->right);//every node
    }
private:
    int maxDepth(TreeNode* root) {
        if(!root) return 0;
        return max(maxDepth(root->left), maxDepth(root->right)) + 1;
    }
};
```

**Improve:** bottom-up, time O(n)

```c++
class Solution {
public:
    bool isBalanced(TreeNode* root) {
        if(!root) return true;
        return dfs(root) != -1;
    }
private:
    //return max depth(>=0) if root is balanced, or -1 unbalanced
    int dfs(TreeNode* root) {
        if(!root) return 0;
        int l = dfs(root->left);
        int r = dfs(root->right);
        if(l == -1 || r == -1 || abs(l-r) > 1) return -1;//slower than top-down!
        return max(l, r) + 1;
    }
};

    //more faster cuz return early!
    int dfs(TreeNode* root) {
        if(!root) return 0;
        int l = dfs(root->left);
        if(l == -1) return -1;
        int r = dfs(root->right);
        if(r == -1) return -1;
        if(abs(l-r) > 1) return -1;
        return max(l, r) + 1;
    }
```



## 111. Minimum Depth of Binary Tree

Easy

Given a binary tree, find its minimum depth.

The minimum depth is the number of nodes along the shortest path from the root node down to the nearest leaf node.

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

return its minimum depth = 2.

**Solution:**

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
    int minDepth(TreeNode* root) {
        if(!root)//no node
            return 0;
        if(!root->left && !root->right)//leaf node
            return 1;
        int left = INT_MAX, right = INT_MAX;
        if(root->left)
            left = minDepth(root->left);
        if(root->right)
            right = minDepth(root->right);
        return min(left, right) + 1;
    }
};

class Solution {
public:
    int minDepth(TreeNode* root) {
        if(!root) return 0;
        int nLeft = minDepth(root->left);
        int nRight = minDepth(root->right);
        if(nLeft==0) return nRight+1;
        if(nRight==0) return nLeft+1;
        return min(nLeft, nRight) + 1;
    }
};
```



## 222. Count Complete Tree Nodes

Medium

Given a **complete** binary tree, count the number of nodes.

**Note:**

**Definition of a complete binary tree from [Wikipedia](http://en.wikipedia.org/wiki/Binary_tree#Types_of_binary_trees):**
In a complete binary tree every level, except possibly the last, is completely filled, and all nodes in the last level are as far left as possible. It can have between 1 and 2h nodes inclusive at the last level h.

**Example:**

```
Input: 
    1
   / \
  2   3
 / \  /
4  5 6

Output: 6
```

**Solution:** time O(2^(h+1)), h: tree height or level, start from 0.

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
    int countNodes(TreeNode* root) {
        if(root)
        {
            //preOrder
            ++count;
            countNodes(root->left);//no need return cuz ++count change class data 'count'
            countNodes(root->right);
        }
        return count;
    }
private:
    int count = 0;
};
```

**Improve:**  time O(logn * logn).

```c++
class Solution {
public:
    int countNodes(TreeNode* root) {        
        if(!root)
            return 0;
        int hLeft = 0, hRight = 0;//hLeft: root down to the left side leaf node height
        TreeNode *l = root, *r = root;
        while(l) {++hLeft; l = l->left;}
        while(r) {++hRight; r = r->right;}
        //cout<<"root->val = "<<root->val<<" hl="<<hLeft<<" hr="<<hRight<<endl;
        if(hLeft == hRight)//a perfect binary tree
            return (1<<hLeft) - 1; //more faster
            //return pow(2, hLeft) - 1;        
        return 1+countNodes(root->left)+countNodes(root->right);
    }
};
```



## 226. Invert Binary Tree

Easy

Invert a binary tree.

**Example:**

Input:

```
     4
   /   \
  2     7
 / \   / \
1   3 6   9
```

Output:

```
     4
   /   \
  7     2
 / \   / \
9   6 3   1
```

**Trivia:**
This problem was inspired by [this original tweet](https://twitter.com/mxcl/status/608682016205344768) by [Max Howell](https://twitter.com/mxcl):

> Google: 90% of our engineers use the software you wrote (Homebrew), but you can’t invert a binary tree on a whiteboard so f*** off.

**Solution:**

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
    TreeNode* invertTree(TreeNode* root) {
        if(root)
        {
            swap(root->left, root->right);//top-down
            invertTree(root->left);
            invertTree(root->right);
        }
        return root;
    }
};

class Solution {
public:
    TreeNode* invertTree(TreeNode* root) {
        if(root)
        {            
            invertTree(root->left);
            invertTree(root->right);
            swap(root->left, root->right);//bottom-up
        }
        return root;
    }
};
```



## 559. Maximum Depth of N-ary Tree

Easy

Given a n-ary tree, find its maximum depth.

The maximum depth is the number of nodes along the longest path from the root node down to the farthest leaf node.

For example, given a `3-ary` tree:

![img](https://assets.leetcode.com/uploads/2018/10/12/narytreeexample.png)

 

We should return its max depth, which is 3.

**Note:**

1. The depth of the tree is at most `1000`.
2. The total number of nodes is at most `5000`.

**Solution 1:** BFS

```c++
/*
// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> children;

    Node() {}

    Node(int _val, vector<Node*> _children) {
        val = _val;
        children = _children;
    }
};
*/
class Solution {
public:
    int maxDepth(Node* root) {
        if (!root) return 0;
        queue<Node*> layer;
        layer.push(root);
        int depth = 0;
        while(!layer.empty())
        {      
            ++depth;
            int size = layer.size();
            for (int i = 0; i < size; ++i)
            {
                Node* node = layer.front();
                layer.pop();
                for (auto* ch: node->children)
                {
                    if (ch)
                        layer.push(ch);
                }
            }
        }
        return depth;
    }
};
```

**Solution 2:** DFS

```c++
class Solution {
public:
    int maxDepth(Node* root) {
        if (!root) return 0;
        int depth = 0;
        for(auto *child: root->children)
        {
            if(child)
            {
                depth = max(depth, maxDepth(child));                
            }
        }
        return depth+1;
    }
};
```



## 653. Two Sum IV - Input is a BST

Easy

Given a Binary Search Tree and a target number, return true if there exist two elements in the BST such that their sum is equal to the given target.

**Example 1:**

```
Input: 
    5
   / \
  3   6
 / \   \
2   4   7

Target = 9

Output: True
```

**Example 2:**

```
Input: 
    5
   / \
  3   6
 / \   \
2   4   7

Target = 28

Output: False
```

**Solution 1:** DFS with hash set and can use BFS too.

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
    bool findTarget(TreeNode* root, int k) {
        unordered_set<int> record;
        return findTarget(root, k, record);
    }
private:
    bool findTarget(TreeNode* node, int k, unordered_set<int>& record) {
        if (!node) return false;
        if (record.find(k - node->val) != record.end())
            return true;
        record.insert(node->val);
        return findTarget(node->left, k, record) || findTarget(node->right, k, record);            
    }
};
```

**Solution 2:** inorder traversal with vector and use 167. input array is sorted

```c++
class Solution {
public:
    bool findTarget(TreeNode* root, int k) {
        if (!root) return false;
        vector<int> record;
        inOrder(root, record);
        return twoSum(record, k);
    }
private:
    void inOrder(TreeNode* node, vector<int>& record) {
        if (!node) return;
        if(node->left)
            inOrder(node->left, record);
        record.push_back(node->val);
        if(node->right)
            inOrder(node->right, record);
        return;
    }
    bool twoSum(vector<int>& nums, int target) {
        int left = 0, right = nums.size()-1;        
        while(left < right)
        {
            int sum = nums[left] + nums[right];
            if(sum == target)
                return true;
            else if (sum < target)
                ++left;
            else
                --right;
        }
        return false;
    }
};
```



# Graph

## 310. Minimum Height Trees

Medium

For an undirected graph with tree characteristics, we can choose any node as the root. The result graph is then a rooted tree. Among all possible rooted trees, those with minimum height are called minimum height trees (MHTs). Given such a graph, write a function to find all the MHTs and return a list of their root labels.

**Format**
The graph contains `n` nodes which are labeled from `0` to `n - 1`. You will be given the number `n` and a list of undirected `edges` (each edge is a pair of labels).

You can assume that no duplicate edges will appear in `edges`. Since all edges are undirected, `[0, 1]` is the same as `[1, 0]` and thus will not appear together in `edges`.

**Example 1 :**

```
Input: n = 4, edges = [[1, 0], [1, 2], [1, 3]]

        0
        |
        1
       / \
      2   3 

Output: [1]
```

**Example 2 :**

```
Input: n = 6, edges = [[0, 3], [1, 3], [2, 3], [4, 3], [5, 4]]

     0  1  2
      \ | /
        3
        |
        4
        |
        5 

Output: [3, 4]
```

**Note**:

- According to the [definition of tree on Wikipedia](https://en.wikipedia.org/wiki/Tree_(graph_theory)): “a tree is an undirected graph in which any two vertices are connected by *exactly* one path. In other words, any connected graph without simple cycles is a tree.”
- The height of a rooted tree is the number of edges on the longest downward path between the root and a leaf.

**Solution: **BFS

```c++
class Solution {
public:
    vector<int> findMinHeightTrees(int n, vector<vector<int>>& edges) {
        vector< vector<int> > adjList(n);
        vector<int> degree(n, 0);
        for(auto& e: edges)
        {
            adjList[e[0]].push_back(e[1]);
            adjList[e[1]].push_back(e[0]);
            ++degree[e[0]];
            ++degree[e[1]];
        }
        
        queue<int> leavesQue;        
        for(int i = 0; i < n; ++i)
        {
            if(degree[i] <= 1)// degree[i] <= 1, i think graph is connected so only use degree[i]==1! But think about the case only have 1 root so the root degree is 0 and put it in leavesQue!
                leavesQue.push(i);
        }
        
        while(n > 2)
        {
            int leavesNum = leavesQue.size();
            n -= leavesNum;
            for (int i = 0; i < leavesNum; ++i)
            {
                int node = leavesQue.front();
                leavesQue.pop();
                for(auto adjNode: adjList[node])
                {
                    if (--degree[adjNode] == 1)
                        leavesQue.push(adjNode);
                }
            }
        }
        
        vector<int> res;
        while(!leavesQue.empty())
        {
            res.push_back(leavesQue.front());
            leavesQue.pop();
        }
        return res;
    }
};
```

# Backtracking

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

**Solution 1:**  enumerate numbers for a position! 对每一个位置选择不同数字来进行全排列！

```c++
class Solution {
public:
    vector<vector<int>> permute(vector<int>& nums) {
        result.clear();
        visited.clear();
        visited.insert(visited.end(), nums.size(), false);
        vector<int> permutations;
        findPermutations(nums, 0, permutations);
        return result;
    }
private:
    //permutations是一个有curNum个元素的全排列
    //在nums中选择一个未被访问过的元素放入permutations，获得一个有curNum+1个元素的排列
    void findPermutations(vector<int>& nums, int curNum, vector<int>& permutations) {
        if(permutations.size() == nums.size())
        {
            result.push_back(permutations);
            return;
        }
        for(int i = 0; i < nums.size(); ++i)
        {
            if(!visited[i])
            {
                visited[i] = true;
                permutations.push_back(nums[i]);
                findPermutations(nums, curNum+1, permutations);
                permutations.pop_back();
                visited[i] = false;
            }
        }
        return;
    }
    vector< vector<int> > result;
    vector<bool> visited;
};
```

**Solution 2:** enumerate positions for a number! 对每一个数字选择不同位置来进行去重全排列！

```c++
class Solution {
public:
    vector<vector<int>> permute(vector<int>& nums) {
        result.clear();
        visited.clear();
        visited.insert(visited.end(), nums.size(), false);
        vector<int> permutations(nums.size());//different!
        findPermutations(nums, 0, permutations);
        return result;
    }
private:
    //permutations是所有元素的一个全排列
    //将nums[curIndex]放入path中未被访问过的位置，然后继续处理nums[curIndex+1]
    void findPermutations(vector<int>& nums, int curIndex, vector<int>& permutations) {
        if(curIndex == nums.size())
        {
            result.push_back(permutations);
            return;
        }
        for(int i = 0; i < permutations.size(); ++i)
        {
            if(!visited[i])
            {
                visited[i] = true;
                permutations[i] = nums[curIndex];
                findPermutations(nums, curIndex+1, permutations);
                visited[i] = false;
            }
        }
        return;
    }
    vector< vector<int> > result;
    vector<bool> visited;
};
```

**Solution 3:** 交换的版本

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



## 47. Permutations II

Medium

Given a collection of numbers that might contain duplicates, return all possible unique permutations.

**Example:**

```
Input: [1,1,2]
Output:
[
  [1,1,2],
  [1,2,1],
  [2,1,1]
]
```

**Solution 1:** enumerate numbers for a position! 对每一个位置选择不同数字来进行去重全排列！

```c++
class Solution {
public:
    vector<vector<int>> permuteUnique(vector<int>& nums) {
        result.clear();
        visited.clear();
        visited.insert(visited.end(), nums.size(), false);
        vector<int> path;
        sort(nums.begin(), nums.end());//关键
        findPermutations(nums, 0, path);
        return result;
    }
private:
    //path是一个有curNum个元素的全排列
    //向path这个排列的末尾添加第curNum+1个元素，获得一个有curNum+1个元素的全排列
    //添加第curNum+1个元素时，若其和前置nums元素相等且前置未被访问过，说明可以直接跳过
    void findPermutations(vector<int>& nums, int curNum, vector<int>& path) {
        if(curNum == nums.size())
        {
            result.push_back(path);
            return;
        }
        for(int i = 0; i < nums.size(); ++i)
        {
            if(visited[i])  continue;//visited[i]表示nums[i]是否被访问过
            if(i > 0 && nums[i] == nums[i-1] && !visited[i-1])  continue;//关键!visited[i]
            visited[i] = true;
            path.push_back(nums[i]);
            findPermutations(nums, curNum+1, path);
            path.pop_back();
            visited[i] = false;
        }
        return;
    }
    vector< vector<int> > result;
    vector<bool> visited;
};
```

**Solution 2:** enumerate positions for a number! 对每一个数字选择不同位置来进行去重全排列！

```c++
class Solution {
public:
    vector<vector<int>> permuteUnique(vector<int>& nums) {
        result.clear();
        visited.clear();
        visited.insert(visited.end(), nums.size(), false);
        vector<int> path(nums.size());//位置初始化！
        sort(nums.begin(), nums.end());
        findPermutations(nums, 0, 0, path);
        return result;
    }
private:
    //path保存元素的全排列
    //将nums[curIndex]放入path中未被访问过的位置
    //保证相对顺序，当nums[curIndex] == nums[curIndex+1]，则nums[curIndex+1]这个元素只能出现在nums[curIndex]元素的后面
    void findPermutations(vector<int>& nums, int curIndex, int startPos, vector<int>& path) {
        if(curIndex == nums.size())
        {
            result.push_back(path);
            return;
        }
        for(int i = startPos; i < path.size(); ++i)
        {
            if(!visited[i])//表示path[i]是否被放入了元素
            {
                visited[i] = true;
                path[i] = nums[curIndex];//nums[curIndex]放在了path[i]
                if(curIndex+1 < nums.size() && nums[curIndex] == nums[curIndex+1])
                    findPermutations(nums, curIndex+1, i+1, path);//nums[curIndex+1]只能放在了path[i+1]及之后
                else
                    findPermutations(nums, curIndex+1, 0, path);//nums[curIndex+1]能放在了path任意未被访问过的位置
                visited[i] = false;
            }
        }
        return;
    }
    vector< vector<int> > result;
    vector<bool> visited;
};
```

**Solution 3:** 交换版本

```c++
class Solution {
public:
    vector<vector<int>> permuteUnique(vector<int>& nums) {
        vector<vector<int>> res;
        if (nums.empty()) return res;
        sort(nums.begin(), nums.end());//sort so no need second swap
        permuteUnique(res, nums, 0);       
        return res;
    }
private:
    void permuteUnique(vector<vector<int>> &res, vector<int> nums, int begin)//not use vector<int>& nums
    {        
        int size = nums.size();
        if(begin == size)
        {
            res.push_back(nums);
            return;
        }
        for(int i = begin; i < size; ++i)
        {
            if(i == begin || nums[i] != nums[begin])
            {
                swap(nums[begin], nums[i]);
                permuteUnique(res, nums, begin+1);
                //swap(nums[begin], nums[i]);
            }
        }
        return;
    }
};
```



## 77. Combinations

Medium

Given two integers *n* and *k*, return all possible combinations of *k* numbers out of 1 ... *n*.

**Example:**

```
Input: n = 4, k = 2
Output:
[
  [2,4],
  [3,4],
  [2,3],
  [1,2],
  [1,3],
  [1,4],
]
```

**Solution:**

```c++
class Solution {
public:
    vector<vector<int>> combine(int n, int k) {
        result.clear();
        vector<int> ivec;
        findCombination(n, k, 1, ivec);
        return result;
    }
    //求解C(n,k), 当前已经找到的组合存储在ivec中，需要从index开始寻找新的元素
    void findCombination(int n, int k, int index, vector<int>& ivec)
    {
        if(ivec.size() == k)
        {
            //cout<<"return, index="<<index<<endl;
            result.push_back(ivec);
            return;
        }
        //cout<<"index="<<index<<endl;
        //还需要k-ivec.size()个元素，所以从[i...n]至少要包含k-ivec.size()个元素
        for(int i = index; i <= n - (k-ivec.size()) + 1; ++i)
        {
            //cout<<"i="<<i<<endl;
            ivec.push_back(i);
            findCombination(n, k, i+1, ivec);
            ivec.pop_back();
        }
        return;
    }
private:
    vector<vector<int>> result;
};
```

