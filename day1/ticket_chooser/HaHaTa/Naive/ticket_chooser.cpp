#include<cstdio>
#include<cstring>
#define MAXN 1005
using namespace std;
int n,m,k,x,l,r,s;
bool map[MAXN][MAXN];
int Abs(int x)
{return (x<0)?(-x):x;}
bool check(int x,int l,int r)
{
	for (int i=l;i<=r;i++)
	if (map[x][i])return 0;
	return 1;
}
int calc(int x,int l,int r)
{
	int xc=(k+1)/2,yc=(k+1)/2,sum=0;
	for (int i=l;i<=r;i++)
	sum+=Abs(x-xc)+Abs(i-yc);
	return sum;
}
int main()
{
	while (scanf("%d%d",&n,&k)!=EOF)
	{
		memset(map,0,sizeof(map));
		while (n--)
		{
			scanf("%d",&m);
			s=0x3f3f3f3f;
			for (int i=1;i<=k;i++)
			for (int j=1;j+m-1<=k;j++)
			if (check(i,j,j+m-1)&&j+m-1<=k)
			{
				int temp=calc(i,j,j+m-1);
				if (temp<s)s=temp,x=i,l=j,r=j+m-1;
				else if (temp==s&&i<x)x=i,l=j,r=j+m-1;
				else if (temp==s&&i==x&&j<l)l=j,r=j+m-1;
			}
			if (s==0x3f3f3f3f)
			{puts("-1");continue;}
			for (int i=l;i<=r;i++)
			map[x][i]=1;
			printf("%d %d %d\n",x,l,r);
		}
	}
	return 0;
}
