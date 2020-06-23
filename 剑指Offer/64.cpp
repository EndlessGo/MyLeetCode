//*剑指 Offer 64. 求1+2+…+n
//求 1+2+...+n ，要求不能使用乘除法、for、while、if、else、switch、case等关键字及条件判断语句（A?B:C）
//1.递归
class Solution {
public:
    int sumNums(int n) {
        //O(n) time, O(n) space
        n && (n += sumNums(n-1));
        return n;
    }
};
