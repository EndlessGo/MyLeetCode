**解题思路：**  
不用+-号完成整数ab的计算。 
Tags :Bit Manipulation  
**1.第一次提交：**  

    class Solution {
	public:
    int getSum(int a, int b) {
        int result = a ^ b ;
        int c = a & b;
        if(c){
            a = result ;
            b = c ;
            result = a ^ b;
            c = a & b;
        }
        return result;
    }
	};
错误：
Input:
2
3
Output:
3
Expected:
5  
分析：进位c=a&b，是本位的进位，求和的时候应该加在高一位上。

**2.第二次提交：**  

	class Solution {
	public:
    int getSum(int a, int b) {
        int result = a ^ b ;
        int c = a & b;
        if(c){
            c = c << 1;
            a = result ;
            b = c ;
            result = a ^ b;
            c = a & b;
        }
        return result;
    }
	};
错误：
Input:
20
30
Output:
34
Expected:
50  
分析：循环之进行了一次，竟然用了if而不是while......无语了。

**3.第三次提交：**  
成功！

	class Solution {
	public:
    int getSum(int a, int b) {
        int result = a ^ b ;
        int c = a & b;
        while(c){
            c = c << 1;
            a = result ;
            b = c ;
            result = a ^ b;
            c = a & b;
        }
        return result;
    }
	}; 
 
**4.别人家的代码一：**   
精炼！ 

	class Solution {
	public:
    int getSum(int a, int b) {
        while(b){
            int c = a & b;
            a = a ^ b ;
            b = c << 1 ;
        }
        return a;
    }
	};
**5.别人家的代码二：**

	class Solution {
	public:
    int getSum(int a, int b) {
        int sum = a;
        
        while (b != 0)
        {
            sum = a ^ b;//calculate sum of a and b without thinking the carry 
            b = (a & b) << 1;//calculate the carry
            a = sum;//add sum(without carry) and carry
        }
        
        return sum;
    }
	};
