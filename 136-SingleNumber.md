**解题思路：**  
不用额外存储空间实现，在线性复杂度内实现，想到用异或的方式，这样两两相同的数异或后直接为0，剩余的单个整数则会返回！  
Tags : Hash Table, Bit Manipulation  
**1.第一次提交：**  

    class Solution {
	public:
    int singleNumber(vector<int>& nums) {
        if(nums.empty()){
            cout<<"empty";
            return 0;
        }
        int length = nums.size();
        int result;
        for(int i = 0; i!= length; ++i)
        {
            result ^= nums[i];
        }
        return result;
    }
	};

**错误：输入[-1],我的输出是-2**  
**分析：**  
result没有初始化`int result;` 

**2.第二次提交：**  
成功。
  
	class Solution {
	public:
    int singleNumber(vector<int>& nums) {
        if(nums.empty()){
            cout<<"empty";
            return 0;
        }
        int length = nums.size();
        int result = 0;
        for(int i = 0; i!= length; ++i)
        {
            result ^= nums[i];
        }
        return result;
    }
	};

**3.别人家的代码一：**  
      
	class Solution {
	public:
    int singleNumber(vector<int>& nums) {
        if(nums.empty()) return 0;
        int first = nums[0];
        for(int i = 1; i<nums.size();i++) {
            first = first ^ nums[i];
        }
        return first;
    }
	};
**简洁性**  
