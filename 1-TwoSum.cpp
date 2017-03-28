class Solution {
public:
	vector<int> twoSum(vector<int>& nums, int target) {
		if(nums.size()<2)        //vector.size()
		{
			cout<<"error";

		}
		vector<int> ivec;
		map<int,int> imap;       //创建map
		int i = 0;
		for(vector<int>::iterator iter = nums.begin(); iter != nums.end(); iter++,i++)
		{
			imap.insert(make_pair(*iter,i));//make_pair(T,T)
		}
		int first,second;        //保存两个索引
		bool flag = false;       //标志：找到另一个元素的索引
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