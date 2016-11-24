#include<cstdio>
using namespace std;
int T,n,m,k;
void error()
{puts("Error!");}
int main()
{
	while (scanf("%d%d",&n,&k)!=EOF)
	{
		if ((++T)>5){error();return 0;}
		if (n>300000){error();return 0;}
		if (!(k&1)){error();return 0;}
		while (n--)
		{
			scanf("%d",&m);
			if (m>k){error();return 0;}
		}
	}
	puts("No Problem.");
	return 0;
}
