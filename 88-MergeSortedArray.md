**解题思路：**  
从尾向前存储，这样遍历一遍就可以完成，移动元素的次数为O(n)。   
Tags : Two Pointers String  
**1.第一次提交：**  

    class Solution {
	public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        if(n == 0) return;
        if(m == 0) for(int i=0; i!=n;++i){nums1[i]=nums2[i];}
        int i = m-1 , j = n-1, k = m+n-1;
        while(i&&j)
        {
            nums1[k--] = (nums1[i]>nums2[j])?nums1[i--]:nums2[j--];
        }
        if(!i)//nums1空，将剩余nums2一到nums1前面
        {
            while(k!=-1)
            {
                nums1[k--] = nums2[k--];
            }
        }
        if(!j){}//nums2空，不用操作
    }
	};

**错误：[-1,3,0,0,0,0,0]
2
[0,0,1,2,3]
5**  
**分析：**  
 `while(i&&j)`i和j的边界值判断有误，应该为-1。 

**2.第二次提交：**  
  
	class Solution {
	public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        if(n == 0) return;
        if(m == 0) for(int i=0; i!=n;++i){nums1[i]=nums2[i];}
        int i = m-1 , j = n-1, k = m+n-1;
        while((i==-1)&&(j==-1))
        {
            nums1[k--] = (nums1[i]>nums2[j])?nums1[i--]:nums2[j--];
        }
        if(i==-1)//nums1空，将剩余nums2一到nums1前面
        {
            while(k!=-1)
            {
                nums1[k--] = nums2[k--];
            }
        }
        if(j==-1){}//nums2空，不用操作
    }
	};
错误：Last executed input:
[0]
0
[1]
1   
分析：应该在前面加上判断  

**3.第三次提交：** 


	class Solution {
	public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        if(nums1.size()<m+n) return;
        if(n == 0) return;
        if(m == 0) 
        {for(int i=0; i!=n;++i){nums1[i]=nums2[i];} return;}
        int i = m-1 , j = n-1, k = m+n-1;
        while((i==-1)&&(j==-1))
        {
            nums1[k--] = (nums1[i]>nums2[j])?nums1[i--]:nums2[j--];
        }
        if(i==-1)//nums1空，将剩余nums2一到nums1前面
        {
            while(k!=-1)
            {
                nums1[k--] = nums2[k--];
            }
        }
        if(j==-1){}//nums2空，不用操作
    }
	}; 
Input:
[1,0]
1
[2]
1
Output:
[1,0]
Expected:
[1,2]  
分析：`while((i==-1)&&(j==-1))`循环条件有误！应该是只要两个数组中有一个为空，就跳出循环`while( !((i==-1)||(j==-1)))` 
 
**4.第四次提交：**

	class Solution {
	public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        if(nums1.size()<m+n) return;
        if(n == 0) return;
        if(m == 0) 
        {for(int i=0; i!=n;++i){nums1[i]=nums2[i];} return;}
        int i = m-1 , j = n-1, k = m+n-1;
        while( !((i==-1)||(j==-1)))
        {
            nums1[k--] = (nums1[i]>nums2[j])?nums1[i--]:nums2[j--];
            cout<<nums1[k+1];
        }
        if(i==-1)//nums1空，将剩余nums2一到nums1前面
        {
            cout<<k;
            while(k != -1)
            {
                nums1[k--] = nums2[k--];
                cout<<nums1[k+1];
            }
        }
        if(j==-1){}//nums2空，不用操作
    }
	}; 
错误：Runtime Error  
分析：`nums1[k--] = nums2[k--];`对k进行了错误操作，改成`nums1[k--] = nums2[j--];`

**5.第五次提交：**
成功！

	class Solution {
	public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        if(nums1.size()<m+n) return;
        if(n == 0) return;
        if(m == 0) 
        {for(int i=0; i!=n;++i){nums1[i]=nums2[i];} return;}
        int i = m-1 , j = n-1, k = m+n-1;
        while( !((i==-1)||(j==-1)))
        {
            nums1[k--] = (nums1[i]>nums2[j])?nums1[i--]:nums2[j--];
            cout<<nums1[k+1];
        }
        if(i==-1)//nums1空，将剩余nums2一到nums1前面
        {
            cout<<k;
            while(k != -1)
            {
                nums1[k--] = nums2[j--];
                cout<<nums1[k+1];
            }
        }
        if(j==-1){}//nums2空，不用操作
    }
	}; 

循环条件`!((i==-1)||(j==-1))`可以简化（等价于）`(i!=-1)&&(j!=-1)`

**6.别人家的代码一：**  
 https://discuss.leetcode.com/topic/16946/4ms-c-solution-with-single-loop/2  

	class Solution {
	public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        int i = m - 1, j = n - 1, tar = m + n - 1;
        while (j >= 0) {
            nums1[tar--] = i >= 0 && nums1[i] > nums2[j] ? nums1[i--] : nums2[j--];
        }
    }
	}; 
