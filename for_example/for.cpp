#include<iostream>
using namespace std;
int sumloop(int n)
{
    int sum=0;
    for(int i=1;i<=n;i++)
    {
        sum+=i;
    }
    return sum;
}
int main()
{
    int sum=0;
    int n=0;
    cout<<"请输入一个数"<<endl;
    cin>>n;
    sum=sumloop(n);
    cout<<"sum="<<sum<<endl;
    return 0;
}