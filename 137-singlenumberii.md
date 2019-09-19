# 137-SingleNumberII

**解题思路：**  
不用额外存储空间实现，在线性复杂度内实现。之前SingleNumber的异或方式行不通了，然后想到使用HashTable，键为整数，值为该整数出现的次数；然后在遍历一遍unordered\_map，找到值只出现一次的整数。其实之前的SingleNumber也可以用这种方式，就是从O\(n\)，现在是O\(2n\)。但问题是：**“Could you implement it without using extra memory?”**卧槽不能使用额外存储！  
Tags : Bit Manipulation  
**1.第一次提交：**  
就通过啦！！开心！但不能使用额外存储！

```text
class Solution {
public:
int singleNumber(vector<int>& nums) {
    unordered_map<int,int> imap;
    if(nums.empty()){return 0;}
    int length = nums.size();
    for(int i = 0; i!= length; ++i){
        imap[nums[i]]++; 
    }
    unordered_map<int,int>::iterator iter = imap.begin();
    for(; iter != imap.end(); ++iter){
        if(iter->second == 1) return iter->first;
    }
}
};
```

**2.别人家的代码一：**  
很详细的数字电路状态转移方法！  
参考[https://discuss.leetcode.com/topic/22821/an-general-way-to-handle-all-this-sort-of-questions/2](https://discuss.leetcode.com/topic/22821/an-general-way-to-handle-all-this-sort-of-questions/2)

```text
class Solution {
public:
int singleNumber(vector<int>& nums) {
    int a=0,b=0;
    int temp = 0;
    int length = nums.size();
    for(int i = 0; i != length; ++i){
        temp = (~a&b&nums[i])|(a&~b&~nums[i]);
        b = (~a&~b&nums[i])|(~a&b&~nums[i]);
        a = temp;
    }
return a|b;
}
};
```

**3.别人家的代码二：** 需要好好学习数电了。

```text
public int singleNumber(int[] A) {
int ones = 0, twos = 0;
for(int i = 0; i < A.length; i++){
    ones = (ones ^ A[i]) & ~twos;
    twos = (twos ^ A[i]) & ~ones;
}
return ones;
}
```

然后用这种方法分析SingleNumber，发现其实对应为两个状态的转移图，就只用一位就可以了，而且这就是异或。

```text
    //# a      c       a
    //# 0      0       0
    //# 1      0       1 
    //# 0      1       1
    //# 1      1       0
class Solution {
public:
int singleNumber(vector<int>& nums) {
    if(nums.empty()){
        cout<<"empty";
        return 0;
    }//可以不用
    int length = nums.size();
    int a=0;
    for(int i = 0; i != length; ++i){
        a = (a&~nums[i])|(~a&nums[i]);
    }
return a;
}
};
```

