**解题思路：**  
不用额外存储空间实现，在线性复杂度内实现，想到用异或的方式，这样两两相同的数异或后直接为0，剩余的单个整数则会返回！  
Tags : Two Pointers String  
**1.第一次提交：**  

    class Solution {
	public:
    int strStr(string haystack, string needle) {
        int haylen = haystack.size() ;
        int neelen = needle.size() ;
        int i = 0 ;
        int j = 0 ;
        while( i != haylen-neelen+1)
        {
            while( j != neelen)
            {
                if(needle[j] == haystack[i]){++j;++i;}
                else{i = i-j; ++i;}
            }
            if(j == neelen){return (i-j);}
        }
        return -1;
    }
	};

**错误：Input:
"mississippi"
"a"
Output:
32
Expected:
-1**  
**分析：**  
 `while( j != neelen)`j一直是0，没有变化。 

**2.第二次提交：**  
  
	class Solution {
	public:
    int strStr(string haystack, string needle) {
        int haylen = haystack.size() ;
        int neelen = needle.size() ;
        int i = 0 ;
        int j = 0 ;
        while(i != haylen-neelen+1 && j != neelen)
        {
            if(needle[j] == haystack[i]){++j;++i;}
            else{i = i-j; ++i;}
        }
        if(j == neelen){return (i-j);}
        return -1;
    }
	};
错误：Input:
"aaa"
"aaa"
Output:
-1
Expected:
0  
分析：
 `while(i != haylen-neelen+1 && j != neelen)`对i的判断有误，若needle长度大于haystack，应该直接在前面加上判断。并且在循环中加入j=0的重置。  

**3.第三次提交：** 
成功！

	class Solution {
	public:
    int strStr(string haystack, string needle) {
        int haylen = haystack.size() ;
        int neelen = needle.size() ;
        if(neelen>haylen){return -1;}
        int i = 0 ;
        int j = 0 ;
        while(i != haylen && j != neelen)
        {
            if(needle[j] == haystack[i]){++j;++i;}
            else{i = i-j; ++i; j=0;}
        }
        if(j == neelen){return (i-j);}
        return -1;
    }
	};  
**4.别人家的代码一：**  
 https://discuss.leetcode.com/topic/15569/explained-4ms-easy-c-solution/2  
还可以利用KMP改进 
