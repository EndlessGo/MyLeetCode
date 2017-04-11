**解题思路：**  
计算x的n次幂：注意幂n的底数的范围，特别是n为负数时候对底数x的处理：n>=0时，x无论何值都能够正常运算；n<0时，如果x=0.0则求0的倒数无意义，当x不是0时可以对x进行(-n)次循环相乘，然后再求倒数（等价于先对x求倒数再进行(-n)次循环）。  
Tags : BinarySearch Math  
**1.第一次提交：**

	class Solution {
	public:
    double myPow(double x, int n) {
        if(n<0&&x==0.0){cout<<"x=0,n<0:error";return 0.0;}
        double result = 1.0;
        if(n<0){n = -n; x = 1/x;}
        while(n--)
        {
            result*=x;
        }
        return result;
    }
};  
**错误：输入x,n分别是0.00001和2147483647时程序超时**  
**分析：**  
当n值非常大的时候O(n)方法不够高效，需要考虑用更高效的方法O(logn)解决。  

**2.第二次提交：**  
  
	class Solution {
	public:
    double BinaryPow(double x, int n)
    {
        if(n==0) return 1.0;
        if(n==1) return x;
        double result = BinaryPow(x,n>>1);
        result *= result;
        if(n&&0x1==1){result*=x;}
        return result;
    }
    double myPow(double x, int n) {
        if(n<0&&x==0.0){cout<<"x=0,n<0:error";return 0.0;}
        if(n<0){n = -n; x = 1/x;}
        //O(n)解法，不够高效，采用二分相乘
        double result = BinaryPow(x,n);
        return result;
    }
	};
**错误：输入x,n分别是1.00000和-2147483648时Runtime Error**  
**分析：**  
int代表的数值范围从-2^31~+2^31-1(-2147483648~+2147483647)。当n=-2^31时，条件判断`if(n<0){n = -n; x = 1/x;}`成立并使得n=2^31超出int范围。改进：用unsigned int 替代int。

**3.第三次提交：**  

	class Solution {
	public:
    bool equal(double num1){
        if((num1-0)>-0.0000001 &&(num1-0)<-0.0000001){return true;}
        else return false;
    }
    double BinaryPow(double x, int n)
    {
        if(n==0) return 1.0;
        if(n==1) return x;
        double result = BinaryPow(x,n>>1);
        result *= result;
        if(n&&0x1==1){result*=x;}
        return result;
    }
    double myPow(double x, int n) {
        if(n<0&&x==0.0){cout<<"x=0,n<0:error";return 0.0;}
        if(n<0){n = -n; x = 1/x;}
        //O(n)解法，不够高效
        double result = BinaryPow(x,n);
        return result;
    }
	};
**错误：**  
Input:
34.00515
-3
Output:
0.00000
Expected:
0.00003  
**分析：**  
`if(n<0){n = -n; x = 1/x;}`改为`if(n<0){exponent = (unsigned int) -n;  x = 1.0/x;}`

**4.第四次提交：**  
**错误：**  
Input:
3.89707
2
Output:
59.18540
Expected:
15.18715  
**分析：**  
按位操作写成了与操作！`if(n&&0x1==1){result*=x;}`改为`if(n&0x1==1){result*=x;}`  

**5.第五次提交：**  
最终通过。  
  
	class Solution {
	public:
    double BinaryPow(double x,unsigned int n)
    {
        if(n==0) return 1.0;
        if(n==1) return x;
        double result = BinaryPow(x,n>>1);
        result *= result;
        if(n&0x1==1){result*=x;}
        return result;
    }
    double myPow(double x, int n) {
        if(n<0&&x==0.0){cout<<"x=0,n<0:error";return 0.0;}
        unsigned int exponent = (unsigned int) n;
        if(n<0){exponent = (unsigned int) -n;  x = 1.0/x;}
        double result = BinaryPow(x,exponent);
        return result;
    }
	};

**6.别人家的代码一：**  
      
	class Solution {
	public:
	double pow(double x, int n) {
    if(n < 0)
        return 1/power(x, -n);
    else 
        return power(x, n);
	}

	double power(double x, int n) {
    double result = 1;
    while(n>0)
    {
        if(n&0x01)
            result *= x;
        x *= x;
        n = n >> 1;
    }
    
    return result;
	}
	};
**简洁性：**  
体会循环`while(l1 && l2)`和条件`if(l1)  p->next=l1;   else    p->next=l2;`的精炼和简单！ 
 
**7.别人家的代码二：**  

	double myPow(double x, int n) {
    if (n==0) return 1;
    if (n==1) return x;
    if (n==-1) return 1/x;
    return myPow(x*x,n/2)*(n%2==0?1:n>0?x:1/x);
	}
**8.别人家的代码三：**  
	class Solution {
	public:
    double myPow(double x, int n) {
    	double ans = 1;
    	unsigned long long p;
    	if (n < 0) {
    		p = -n;
    		x = 1 / x;
    	} else {
    		p = n;
    	}
		while (p) {
			if (p & 1)
				ans *= x;
			x *= x;
			p >>= 1;
		}
		return ans;
    }
	};