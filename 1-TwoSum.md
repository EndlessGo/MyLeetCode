**题目大意：**给一个整型数组，返回两个下标，这两个下标对应整数的和正好是给定目标的数值。  
例子：nums=[2,7,11,15],target = 9, num[0] + num[1] = 2 + 7 =9,return [0,1].  

**解题思路：**首先想到的自然是从头到尾遍历整个数组，最坏情况是return[0,n-1]，[1,n-1]...[n-2,n-1],复杂度为n(n-1)/2，是O(n^2)解法。当然肯定不是最好的，于是想到用Array+HashTable的方式  
，先遍历一次数组建立哈希表O(n)，然后在哈希表中寻找（目标值-第一个值）的O(1)的方式，最差O(n-1)，找到或找不到合适的第二个值，返回下标。  

**1.下面是Array+HashTable思路代码，在1-TwoSum1.cpp中：**

	class Solution {
		public:
		vector<int> twoSum(vector<int>& nums, int target) {
			if(nums.size()<2)//vector.size()
			{
				cout<<"error";
	
			}
			vector<int> ivec;
			map<int,int> imap;   //创建map
			int i = 0;
			for(vector<int>::iterator iter = nums.begin(); iter != nums.end(); iter++,i++)
			{
				imap.insert(make_pair(*iter,i));//make_pair(T,T)
			}
			int first,second;//保存两个索引
			bool flag = false;   //标志：找到另一个元素的索引
			first = 0;
			while(!flag)
			{
				map<int,int>::iterator it = imap.find(target-nums[first]);			
				if(it != imap.end()) //vector[i]
				{//查找，返回迭代器
					second = it->second;
					if (first != second)
					{
						flag = true;
						break;
					}
				}
				first ++;
				if (first == nums.size())
					break;
			}
			if(first!=nums.size()&&flag==true)
			{
				ivec.push_back(first);
				ivec.push_back(second);
			}
			else{cout<<"未找到";}
			return ivec;
		}
	};
注意语句`if (first != second)` 的含义。  
例如，nums = [3 2 4],target = 6, (target-nums[0])=3,会返回两个下标为0。这是不可取的。  
**2.下面是Array+HashTable思路代码，在1-TwoSum2.cpp中：**  
   
    class Solution {
    public:
    	vector<int> twoSum(vector<int>& nums, int target);
    };
    
    vector<int> Solution::twoSum(vector<int>& nums, int target)
    {
    	unordered_map<int, int> my_map;
    	vector<int> ans;
    
    	for(int i = 0; i < nums.size(); i++)//用vector下标形式nums[i]创建unordered_map的键值对
    	{
    		my_map.insert(pair<int, int>(nums[i], i));
    	}
    
    	for(int i = 0; i < nums.size(); i++)//在my_map中对target - nums[i]查找，返回迭代器的键(i,即it->first)值(it->second)；
    	{
    		auto it = my_map.find(target - nums[i]);
    
    		if(it != my_map.end() && i != it->second)
    		{
    			ans.push_back(i);
    			ans.push_back(it->second);
    			break;
    
    		}
    	}
    
    	return ans;
    }

**3.区别与总结：**  
map内部实现了一个红黑树，该结构具有自动排序的功能，因此map内部的所有元素都是有序的，红黑树的每一个节点都代表着map的一个元素，因此，对于map进行的查找，删除，添加等一系列的操作都相当于是对红黑树进行这样的操作，故红黑树的效率决定了map的效率。  
unordered_map内部实现了一个哈希表，因此其元素的排列顺序是杂乱的，无序的。  
注意代码的简洁！  
**4.下面是更简洁的代码思路：**  

    class Solution {
    public:
    	vector<int> twoSum(vector<int>& nums, int target)
    {
    //Key is the number and value is its index in the vector.
    	unordered_map<int, int> hash;
    	vector<int> result;
    	for (int i = 0; i < nums.size(); i++) {
    		int numberToFind = target - nums[i];
    
    //if numberToFind is found in map, return them
    		if (hash.find(numberToFind) != hash.end()) {
    //+1 because indices are NOT zero based
    			result.push_back(hash[numberToFind]);
    			result.push_back(i);			
    			return result;
    		}
    
    //number was not found. Put it in the map.
    		hash[nums[i]] = i;
    	}
    	return result;
    }
    };
思路：初始unordered_map中没有pair对，每新增加一个元素`nums[i]`，对应在**前面**已经建立的hash表中寻找配对元素`hash.find(numberToFind)`。**因此是一个插入新元素时前向查找的思路。**  
其中对于重复元素的判别体现在`hash.find(numberToFind)`查找是在`hash[nums[i]] = i;`添加自身之前的，因此不会找到自己。