#include<cstdio>
#include<cstring>
#define MAXN 305
#define MAXL 10
using namespace std;
int n,m;
char ch[MAXN][MAXL];
bool check(int x)
{
	if (strlen(ch[x])==2)
	{
		if (ch[x][0]=='A'&&ch[x][1]=='X')return 1;
		if (ch[x][0]=='B'&&ch[x][1]=='X')return 1;
		if (ch[x][0]=='C'&&ch[x][1]=='X')return 1;
		if (ch[x][0]=='D'&&ch[x][1]=='X')return 1;
		return 0;
	}
	if (strlen(ch[x])==3)
	{
		if (ch[x][0]=='T'&&ch[x][1]=='A'&&ch[x][2]=='X')return 1;
		if (ch[x][0]=='T'&&ch[x][1]=='B'&&ch[x][2]=='X')return 1;
		if (ch[x][0]=='T'&&ch[x][1]=='C'&&ch[x][2]=='X')return 1;
		if (ch[x][0]=='T'&&ch[x][1]=='D'&&ch[x][2]=='X')return 1;
		return 0;
	}
	if (strlen(ch[x])==4)
	{
		if ((ch[x][0]<'0'||ch[x][0]>'9')&&(ch[x][0]<'A'||ch[x][0]>'F'))return 0;
		if ((ch[x][1]<'0'||ch[x][1]>'9')&&(ch[x][1]<'A'||ch[x][1]>'F'))return 0;
		if ((ch[x][2]<'0'||ch[x][2]>'9')&&(ch[x][2]<'A'||ch[x][2]>'F'))return 0;
		if ((ch[x][3]<'0'||ch[x][3]>'9')&&(ch[x][3]<'A'||ch[x][3]>'F'))return 0;
		return 1;
	}
	if (strlen(ch[x])==5)
	{
		if (ch[x][0]!='T')return 0;
		if ((ch[x][1]<'0'||ch[x][1]>'9')&&(ch[x][1]<'A'||ch[x][1]>'F'))return 0;
		if ((ch[x][2]<'0'||ch[x][2]>'9')&&(ch[x][2]<'A'||ch[x][2]>'F'))return 0;
		if ((ch[x][3]<'0'||ch[x][3]>'9')&&(ch[x][3]<'A'||ch[x][3]>'F'))return 0;
		if ((ch[x][4]<'0'||ch[x][4]>'9')&&(ch[x][4]<'A'||ch[x][4]>'F'))return 0;
		return 1;
	}
	return 0;
}
int main()
{
	while (scanf("%s",ch[++m])!=EOF);m--;
	if (strcmp(ch[1],"RUN"))
	{
		puts("The first instruction is not RUN.");
		return 0;
	}
	if (strcmp(ch[m],"STOP"))
	{
		puts("The last instruction is not STOP.");
		return 0;
	}
	for (int i=2;i<m;i++)
	{
		if (!strcmp(ch[i],"RUN"))
		{
			puts("More than one RUN.");
			return 0;
		}
		if (!strcmp(ch[i],"STOP"))
		{
			puts("More than one STOP.");
			return 0;
		}
	}
	for (int i=1;i<=m;i++)
	for (int j=0;j<strlen(ch[i]);j++)
	if ((ch[i][j]<'A'||ch[i][j]>'Z')&&(ch[i][j]<'0'||ch[i][j]>'9'))
	{
		puts("Illegal char in data.");
		return 0;
	}
	for (int i=1;i<=m;i++)
	{
		if (!strcmp(ch[i],"RUN"))continue;
		if (!strcmp(ch[i],"STOP"))continue;
		if (!strcmp(ch[i],"ECHO"))
		{
			if (!check(i+1))
			{
				puts("Illegal Operation in data.");
				return 0;
			}
			i++;continue;
		}
		if (!strcmp(ch[i],"ADD"))
		{
			if ((!check(i+1))||(!check(i+2)))
			{
				puts("Illegal Operation in data.");
				return 0;
			}
			if ((strlen(ch[i+1])==5)&&(strlen(ch[i+2])==5))
			{
				puts("Illegal Operation in data.");
				return 0;
			}
			i+=2;continue;
		}
		if (!strcmp(ch[i],"INC"))
		{
			if (!check(i+1))
			{
				puts("Illegal Operation in data.");
				return 0;
			}
			i++;continue;
		}
		if (!strcmp(ch[i],"MOV"))
		{
			if ((!check(i+1))||(!check(i+2)))
			{
				puts("Illegal Operation in data.");
				return 0;
			}
			if ((strlen(ch[i+1])==5)&&(strlen(ch[i+2])==5))
			{
				puts("Illegal Operation in data.");
				return 0;
			}
			i+=2;continue;
		}
		if (!strcmp(ch[i],"CMP"))
		{
			if ((!check(i+1))||(!check(i+2)))
			{
				puts("Illegal Operation in data.");
				return 0;
			}
			if ((strlen(ch[i+1])==5)&&(strlen(ch[i+2])==5))
			{
				puts("Illegal Operation in data.");
				return 0;
			}
			i+=2;continue;
		}
		if (!strcmp(ch[i],"JMP"))
		{
			if (!check(i+1))
			{
				puts("Illegal Operation in data.");
				return 0;
			}
			i++;continue;
		}
		if (!strcmp(ch[i],"JG"))
		{
			if (!check(i+1))
			{
				puts("Illegal Operation in data.");
				return 0;
			}
			i++;continue;
		}
		if (!strcmp(ch[i],"JL"))
		{
			if (!check(i+1))
			{
				puts("Illegal Operation in data.");
				return 0;
			}
			i++;continue;
		}
		if (!strcmp(ch[i],"JE"))
		{
			if (!check(i+1))
			{
				puts("Illegal Operation in data.");
				return 0;
			}
			i++;continue;
		}
		if (!strcmp(ch[i],"JNG"))
		{
			if (!check(i+1))
			{
				puts("Illegal Operation in data.");
				return 0;
			}
			i++;continue;
		}
		if (!strcmp(ch[i],"JNL"))
		{
			if (!check(i+1))
			{
				puts("Illegal Operation in data.");
				return 0;
			}
			i++;continue;
		}
		if (!strcmp(ch[i],"JNE"))
		{
			if (!check(i+1))
			{
				puts("Illegal Operation in data.");
				return 0;
			}
			i++;continue;
		}
		puts("Unknown instruction in data.");
		return 0;
	}
	puts("No problem!");
	return 0;
}
