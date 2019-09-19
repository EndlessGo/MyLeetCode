# 1

​	哈哈哈哈哈哈哈哈哈

的顶顶顶顶顶顶顶

## 1.1

的顶顶顶顶顶顶顶

## 1.2

的顶顶顶顶顶顶顶

# 2

的顶顶顶顶顶顶顶



```c++
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

