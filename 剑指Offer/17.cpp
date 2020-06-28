//剑指 Offer 17. 打印从1到最大的n位数
//1. 不考虑大数问题
class Solution {
public:
    vector<int> printNumbers(int n) {
        //O(10^n) time, O(1) space
        int end = pow(10,n);
        vector<int> res(end-1, 0);
        for (int i = 1; i < end; ++i)
            res[i-1] = i;
        return res;
    }
};

//2. 全排列，字符串转数字太耗时了
class Solution {
private:
	vector<int> res;
        //O(10^n) time, O(n) space
public:
	vector<int> printNumbers(int n) {
		if (n <= 0) return res;
		string numbers(n, '0');
		Permutation(numbers, 0);
		return res;
	}
	void Permutation(string& numbers, int index)
	{
		if (index == numbers.length())
		{
			SaveNumber(numbers);
			return;
		}
		for (int i = 0; i <= 9; ++i)
		{
			numbers[index] = '0' + i;
			Permutation(numbers, index+1);
		}
		return;
	}
	void SaveNumber(const string& numbers)
	{
		string s = "";
		bool isBegin0 = true;
		string::const_iterator it = numbers.begin();
		while (it != numbers.end())
		{
			if (isBegin0 && *it != '0') isBegin0 = false;
			if (!isBegin0)
			{
				s += *it;
			}
			it++;
		}
		if (s != "")
		{
			int num = stoi(s);
			res.push_back(num);
		}
	}
};
