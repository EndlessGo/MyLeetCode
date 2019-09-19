# 27-RemoveElement

**解题思路：**  
一头一尾判断是否为字母。使用isalnum\(\)和tolower\(\)函数。  
Tags: Array Two Pointers  
**1.第一次提交：**  
成功。 class Solution { public: int removeElement\(vector& nums, int val\) { int length = nums.size\(\); int newlen = length; for\(int i = 0; i != length; ++i\) { if\(nums\[i\]==val\){--newlen;nums\[i\]=INT\_MAX;} } vector::iterator iter = nums.begin\(\); sort\(iter,iter+length\); return newlen; } };

**2.别人家的代码一：**  
[https://leetcode.com/articles/remove-element/\#approach-1-two-pointers-accepted](https://leetcode.com/articles/remove-element/#approach-1-two-pointers-accepted)

```text
public int removeElement(int[] nums, int val) {
int i = 0;
for (int j = 0; j < nums.length; j++) {
    if (nums[j] != val) {
        nums[i] = nums[j];
        i++;
    }
}
return i;
}
```

**3.别人家的代码二：**  
[https://leetcode.com/articles/remove-element/\#approach-1-two-pointers-accepted](https://leetcode.com/articles/remove-element/#approach-1-two-pointers-accepted)

```text
public int removeElement(int[] nums, int val) {
int i = 0;
int n = nums.length;
while (i < n) {
    if (nums[i] == val) {
        nums[i] = nums[n - 1];
        // reduce array size by one
        n--;
    } else {
        i++;
    }
}
return n;
}
```

**3.别人家的代码二：**

```text
int removeElement(vector<int>& nums, int val) {
int cnt = 0;
for(int i = 0 ; i < nums.size() ; ++i) {
    if(nums[i] == val)
        cnt++;
    else
        nums[i-cnt] = nums[i];
}
return nums.size()-cnt;
}
```

