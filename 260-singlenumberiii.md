# 260-SingleNumberIII

**解题思路：**  
Could you implement it using only constant space complexity?在常数空间复杂度和线性时间复杂度内实现！  
Tags :Bit Manipulation  
**1.第一次提交：**  
成功！但空间复杂度不符合要求！需要常数空间复杂度。

```text
class Solution {
public:
vector<int> singleNumber(vector<int>& nums) {
    vector<int> result;
    unordered_map<int,int> imap;
    if(nums.empty()){return result;}
    int length = nums.size();
    for(int i = 0; i!= length; ++i){
        imap[nums[i]]++; 
    }
    unordered_map<int,int>::iterator iter = imap.begin();
    for(; iter != imap.end(); ++iter){
        if(iter->second == 1) result.push_back(iter->first);
    }
    return result;
}
};
```

**2.别人家的代码一：**  
[https://discuss.leetcode.com/topic/21605/accepted-c-java-o-n-time-o-1-space-easy-solution-with-detail-explanations](https://discuss.leetcode.com/topic/21605/accepted-c-java-o-n-time-o-1-space-easy-solution-with-detail-explanations)  
核心思想：把原来的vector分成两组，分组依据是两个不同整数异或后的第一个set bit，也就是第一个不同的位。  
步骤：  
1.数组全部XOR操作，得到a^b（a与b是只出现一次的整数）的位，然后找到第一个set bit，位为“1”的位。  
2.根据set bit，对原来的数组进行分组，因为两个相同的整数肯定还是分到同一个组，所以分别对两组进行异或可以求出a和b。

```text
class Solution
{
public:
vector<int> singleNumber(vector<int>& nums) 
{
    // Pass 1 : 
    // Get the XOR of the two numbers we need to find
    int diff = accumulate(nums.begin(), nums.end(), 0, bit_xor<int>());
    // Get its last set bit
    //“与”操作：与自己的负数很精彩，只留下了一位1
    diff &= -diff;

    // Pass 2 :
    vector<int> rets = {0, 0}; // this vector stores the two numbers we will return
    for (int num : nums)
    {
        if ((num & diff) == 0) // the bit is not set
        {
            rets[0] ^= num;
        }
        else // the bit is set
        {
            rets[1] ^= num;
        }
    }
    return rets;
}
};
```

**进一步学习：** accumulate和位操作！

