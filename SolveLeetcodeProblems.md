[TOC]



# Array

## 1. Two Sum

Easy

Given an array of integers, return **indices** of the two numbers such that they add up to a specific target.

You may assume that each input would have **exactly** one solution, and you may not use the *same* element twice.

**Example:**

```
Given nums = [2, 7, 11, 15], target = 9,

Because nums[0] + nums[1] = 2 + 7 = 9,
return [0, 1].
```

**Solution:**

```c++
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int,int> valIndexMap;        
        for (int i = 0; i < nums.size(); ++i)
        {
            auto iter = valIndexMap.find(target-nums[i]);
            if (iter == valIndexMap.end())
            {
                valIndexMap.insert(pair<int,int>(nums[i],i));
            }
            else
            {                   
                return vector<int>{iter->second, i};
            }
        }
        throw "no solution";
    }
};
```

**Improve:**

```c++
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int,int> valIndexMap;
        int size = nums.size();
        auto end = valIndexMap.end();
        vector<int> res;
        for (int i = 0; i < size; ++i)
        {
            if (valIndexMap.find(target-nums[i]) != end)
            {
                res.push_back(valIndexMap[target-nums[i]]);
                res.push_back(i);
                break;
            }
            valIndexMap[nums[i]] = i;
        }
        return res;
    }
};
```

# Linked List

## 2. Add Two Numbers