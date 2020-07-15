//1. 找出数组中元素和为指定值的所有组合
//https://blog.csdn.net/cxxmaker/article/details/7165947
#include <iostream>
using namespace std;

void solve(int n, int data[], int start, int end,
	int used[], int index, int size, bool change)
{
	if (0 == n && change) {
		for (int i = 0; i <= index; ++i) {
			cout << used[i] << " ";
		}
		cout << endl;
	}
	// cause zero may in the data array, we cannot jump out now
	if (start < end && index < size - 1) {
		if (n >= data[start]) {
			++index;
			used[index] = data[start];
			solve(n - data[start], data, start + 1, end, used, index, size, true);
			--index;
		}
		solve(n, data, start + 1, end, used, index, size, false);
	}
}

void solve(int n, int data[], int used[], int size)
{
	solve(n, data, 0, size, used, -1, size, false);
}

int main()
{
	{
		cout << "------ block 1 ------" << endl;
		int n = 15;
		int data[10] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
		int used[10] = { 0 };
		solve(n, data, used, 10);
	}

	{
		cout << "------ block 2 ------" << endl;
		int n = 15;
		int data[10] = { 9, 8, 7, 6, 5, 4, 3, 2, 1, 0 };
		int used[10] = { 0 };
		solve(n, data, used, 10);
	}

	return 0;
}

//2.https://blog.csdn.net/li_chong/article/details/8881524
#include<stdio.h>
 
int ok;//是否存在这样的组合
int total,n,data[12];//数据存储
int count,ans[12];//结果存储
 
void dfs(int i,int sum)
{
	int j;
	if(sum==total)
	{
		ok=1;
		for(j=1,printf("%d",ans[0]);j<count;j++) printf("+%d",ans[j]);
		printf("\n");
		return;
	}
	if(i>=n || sum>total) return;
	for(j=i;j<n;j++)
	{
		//以下的处理避免了重复的情况
		if(j==i || data[j]!=data[j-1])
		{
			ans[count++]=data[j];
			dfs(j+1,sum+data[j]);
			count--;
		}
	}
}
 
int main()
{
	int i;	
	while(scanf("%d%d",&total,&n)!=EOF && n)
	{
		for(i=0;i<n;i++)
		{
			scanf("%d",&data[i]);
		}
		
		printf("Sums of %d:\n",total);
		ok=count=0;
		dfs(0,0);
		if(ok==0) printf("NONE\n");
	}
	return 0;
}

