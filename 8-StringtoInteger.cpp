class Solution {
public:
    int myAtoi(string str) {
        if(str.empty())//empty()判断是否为空
        {
            cout<<"empty stirng";
            return 0;
        }
        int result = 0;
        int sign = 1;//默认正数
        int signnumber = 0;//正负号的个数，最多只能有一个
        bool spaceflag = true;//true代表字符串前面的空格
        for(int i=0 ; i!=str.size();i++)
        {
            if(str[i]==' '&&spaceflag){continue;}//判断是字符串前面的空格还是字符串后面的空格
            if(str[i]=='+' && signnumber<1)//判断第一位的正负号
            {
                sign = 1;//正号
                signnumber++;
                spaceflag = false;//只要不是前面的空格，就是后面的空格了！
                continue;
            }
            if(str[i]=='-'&& signnumber<1)//判断第一位的正负号
            {
                sign = -1;//负号
                signnumber++;
                spaceflag = false;
                continue;
            }
            if(str[i]<'0'||str[i]>'9'||str[i]==' ')
            {
                cout<<"meet a char or space";
                return sign*result;//返回前面的整数
            }
            else
            {
                result = result*10+(str[i]-'0');//注意-'0
            }
            spaceflag = false;
        }
        if(str.size()>8*sizeof(int))//判断是否溢出
        {
            cout<<"string too long";
        }        
        return sign*result;
    }
};