#include<cstdio>
#include<algorithm>
#define MAXN 300005
using namespace std;
int n,m,k;
int s,x,l,r;
int L[MAXN],R[MAXN];
int Abs(int x)
{return (x<0)?(-x):x;}
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
		for (int i=1;i<=k;i++)
		L[i]=R[i]=(k+1)/2;
		while (n--)
		{
			scanf("%d",&m);
			s=0x3f3f3f3f;
			for (int i=1;i<=k;i++)
			{
				int temp;
				if (L[i]==R[i]&&(m&1))
				{
					temp=calc(i,(k+1)/2-(m+1)/2+1,(k+1)/2-(m+1)/2+m);
					if (temp<s)s=temp,x=i,l=(k+1)/2-(m+1)/2+1,r=(k+1)/2-(m+1)/2+m;
					else if (temp==s&&i<x)x=i,l=(k+1)/2-(m+1)/2+1,r=(k+1)/2-(m+1)/2+m;
					else if (temp==s&&i==x&&(k+1)/2-(m+1)/2+1<l)l=(k+1)/2-(m+1)/2+1,r=(k+1)/2-(m+1)/2+m;
				}
				else if (L[i]==R[i])
				{
					temp=calc(i,(k+1)/2-m/2,(k+1)/2+m/2-1);
					if (temp<s)s=temp,x=i,l=(k+1)/2-m/2,r=(k+1)/2+m/2-1;
					else if (temp==s&&i<x)x=i,l=(k+1)/2-m/2,r=(k+1)/2+m/2-1;
					else if (temp==s&&i==x&&(k+1)/2-m/2<l)l=(k+1)/2-m/2,r=(k+1)/2+m/2-1;
				}
				if (L[i]>=m)
				{
					temp=calc(i,L[i]-m+1,L[i]);
					if (temp<s)s=temp,x=i,l=L[i]-m+1,r=L[i];
					else if (temp==s&&i<x)x=i,l=L[i]-m+1,r=L[i];
					else if (temp==s&&i==x&&L[i]-m+1<l)l=L[i]-m+1,r=L[i];
				}
				if (R[i]+m-1<=k)
				{
					temp=calc(i,R[i],R[i]+m-1);
					if (temp<s)s=temp,x=i,l=R[i],r=R[i]+m-1;
					else if (temp==s&&i<x)x=i,l=R[i],r=R[i]+m-1;
					else if (temp==s&&i==x&&R[i]<l)l=R[i],r=R[i]+m-1;
				}
			}
			if (s==0x3f3f3f3f){puts("-1");continue;}
			L[x]=min(L[x],l-1);R[x]=max(R[x],r+1);
			printf("%d %d %d\n",x,l,r);
		}
	}
	return 0;
}
