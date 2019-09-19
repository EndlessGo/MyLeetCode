# 125-ValidPalindrome

**解题思路：**  
一头一尾判断是否为字母。使用isalnum\(\)和tolower\(\)函数。  
Tags : Two Pointers String  
**1.第一次提交：**

```text
class Solution {
public:
bool isPalindrome(string s) {
    int i = 0, j = s.size()-1;
    while(i<=j)
    {
        while(!isalnum(s[i])) ++i;
        while(!isalnum(s[j])) --j;
        if(tolower(s[i])==tolower(s[j])){++i;--j;}
        else{return false;}
    }
    return true;
}
};
```

错误： Input: "''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''" Output: false Expected: true  
分析：  
`while(!isalnum(s[i])) ++i; while(!isalnum(s[j])) --j;`不该用while。

**2.第二次提交：**

```text
class Solution {
public:
bool isPalindrome(string s) {
    int i = 0, j = s.size()-1;
    while(i<=j)
    {
        if(!isalnum(s[i])) {++i;continue;}
        if(!isalnum(s[j])) {--j;continue;}
        if(tolower(s[i])==tolower(s[j])){++i;--j;}
        else{return false;}
    }
    return true;
}
};
```

**3.别人家的代码一：**

```text
class Solution {
public:
bool isPalindrome(string s) {
    int l = 0, r = s.length() - 1; 
    while (l < r) {
        while (l < r && !isalnum(s[l])) l++;
        while (r > l && !isalnum(s[r])) r--; 
        if (toupper(s[l++]) != toupper(s[r--]))
            return false;
    }
    return true; 
}
};
```

