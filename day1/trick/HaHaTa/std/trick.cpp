#include<cstdio>
#include<cstring>
#define MAX 65536
#define MAXL 10
#define MAXN 105
#define MAXS 100005
#define LIM 1000000
using namespace std;

int n,x[MAXL],save[MAXS];
int step,cnt,cmpa,cmpb,tpx;
bool flag;
char od[MAXL],oda[MAXL],odb[MAXL];

struct order
{
	int type,jmp;
	int ta,a;
	int tb,b;
	order(){}
	order(int _type)
	{
		type=_type;
		jmp=ta=a=tb=b=0;
	}
	order(int _type,int _ta,int _a)
	{
		type=_type;ta=_ta;a=_a;
		jmp=tb=b=0;
	}
	order(int _type,int _ta,int _a,int _tb,int _b)
	{
		type=_type;ta=_ta;a=_a;tb=_tb;b=_b;
		jmp=0;
	}
	order(int _type,int _jmp,int _ta,int _a)
	{
		type=_type;jmp=_jmp;ta=_ta;a=_a;
		tb=b=0;
	}
}ins[MAXN];

int exa(int l,int r)
{
	int val=0;
	if (oda[l+1]=='X')return 'A'-oda[l]-1;
	for (int i=l;i<=r;i++)
	{
		val*=16;
		if ((oda[i]>='0')&&(oda[i]<='9'))val+=oda[i]-'0';
		else val+=oda[i]-'A'+10;
	}
	return val;
}

int exb(int l,int r)
{
	int val=0;
	if (odb[l+1]=='X')return 'A'-odb[l]-1;
	for (int i=l;i<=r;i++)
	{
		val*=16;
		if ((odb[i]>='0')&&(odb[i]<='9'))val+=odb[i]-'0';
		else val+=odb[i]-'A'+10;
	}
	return val;
}

void init()
{
	while (true)
	{
		scanf("%s",od);
		if (!strcmp(od,"RUN"))
		{
			ins[++n]=order(1);
			continue;
		}
		if (!strcmp(od,"STOP"))
		{
			ins[++n]=order(2);
			break;
		}
		if (!strcmp(od,"ECHO"))
		{
			scanf("%s",oda);
			if (oda[0]=='T')ins[++n]=order(3,1,exa(1,4));
			else ins[++n]=order(3,0,exa(0,3));
			continue;
		}
		if (!strcmp(od,"ADD"))
		{
			scanf("%s%s",oda,odb);
			if ((oda[0]=='T')&&(odb[0]=='T'))ins[++n]=order(4,1,exa(1,4),1,exb(1,4));
			else if (oda[0]=='T')ins[++n]=order(4,1,exa(1,4),0,exb(0,3));
			else if (odb[0]=='T')ins[++n]=order(4,0,exa(0,3),1,exb(1,4));
			else ins[++n]=order(4,0,exa(0,3),0,exb(0,3));
			continue;
		}
		if (!strcmp(od,"INC"))
		{
			scanf("%s",oda);
			if (oda[0]=='T')ins[++n]=order(5,1,exa(1,4));
			else ins[++n]=order(5,0,exa(0,3));
			continue;
		}
		if (!strcmp(od,"MOV"))
		{
			scanf("%s%s",oda,odb);
			if ((oda[0]=='T')&&(odb[0]=='T'))ins[++n]=order(6,1,exa(1,4),1,exb(1,4));
			else if (oda[0]=='T')ins[++n]=order(6,1,exa(1,4),0,exb(0,3));
			else if (odb[0]=='T')ins[++n]=order(6,0,exa(0,3),1,exb(1,4));
			else ins[++n]=order(6,0,exa(0,3),0,exb(0,3));
			continue;
		}
		if (!strcmp(od,"CMP"))
		{
			scanf("%s%s",oda,odb);
			if ((oda[0]=='T')&&(odb[0]=='T'))ins[++n]=order(7,1,exa(1,4),1,exb(1,4));
			else if (oda[0]=='T')ins[++n]=order(7,1,exa(1,4),0,exb(0,3));
			else if (odb[0]=='T')ins[++n]=order(7,0,exa(0,3),1,exb(1,4));
			else ins[++n]=order(7,0,exa(0,3),0,exb(0,3));
			continue;
		}
		if (!strcmp(od,"JMP"))
		{
			scanf("%s",oda);
			if (oda[0]=='T')ins[++n]=order(8,0,1,exa(1,4));
			else ins[++n]=order(8,0,0,exa(0,3));
			continue;
		}
		if (!strcmp(od,"JG"))
		{
			scanf("%s",oda);
			if (oda[0]=='T')ins[++n]=order(8,1,1,exa(1,4));
			else ins[++n]=order(8,1,0,exa(0,3));
			continue;
		}
		if (!strcmp(od,"JL"))
		{
			scanf("%s",oda);
			if (oda[0]=='T')ins[++n]=order(8,2,1,exa(1,4));
			else ins[++n]=order(8,2,0,exa(0,3));
			continue;
		}
		if (!strcmp(od,"JE"))
		{
			scanf("%s",oda);
			if (oda[0]=='T')ins[++n]=order(8,3,1,exa(1,4));
			else ins[++n]=order(8,3,0,exa(0,3));
			continue;
		}
		if (!strcmp(od,"JNG"))
		{
			scanf("%s",oda);
			if (oda[0]=='T')ins[++n]=order(8,4,1,exa(1,4));
			else ins[++n]=order(8,4,0,exa(0,3));
			continue;
		}
		if (!strcmp(od,"JNL"))
		{
			scanf("%s",oda);
			if (oda[0]=='T')ins[++n]=order(8,5,1,exa(1,4));
			else ins[++n]=order(8,5,0,exa(0,3));
			continue;
		}
		if (!strcmp(od,"JNE"))
		{
			scanf("%s",oda);
			if (oda[0]=='T')ins[++n]=order(8,6,1,exa(1,4));
			else ins[++n]=order(8,6,0,exa(0,3));
			continue;
		}
	}
}

void debug_init()
{
	for (int i=1;i<=n;i++)
	{
		if (ins[i].type==1)printf("RUN ");
		if (ins[i].type==2)printf("STOP ");
		if (ins[i].type==3)printf("ECHO ");
		if (ins[i].type==4)printf("ADD ");
		if (ins[i].type==5)printf("INC ");
		if (ins[i].type==6)printf("MOV ");
		if (ins[i].type==7)printf("CMP ");
		if (ins[i].type==8)
		{
			if (ins[i].jmp==0)printf("JMP ");
			if (ins[i].jmp==1)printf("JG ");
			if (ins[i].jmp==2)printf("JL ");
			if (ins[i].jmp==3)printf("JE ");
			if (ins[i].jmp==4)printf("JNG ");
			if (ins[i].jmp==5)printf("JNL ");
			if (ins[i].jmp==6)printf("JNE ");
		}
		printf("%d %d %d %d\n",ins[i].a,ins[i].ta,ins[i].b,ins[i].tb);
	}
}

bool re(int pos)
{return (pos<12288)||(pos>=45056);}

void ex(int val)
{
	int a,b,c,d;
	a=val/4096;val-=a*4096;
	b=val/256;val-=b*256;
	c=val/16;val-=c*16;
	d=val;
	if (a<10)putchar('0'+a);else putchar('A'+a-10);
	if (b<10)putchar('0'+b);else putchar('A'+b-10);
	if (c<10)putchar('0'+c);else putchar('A'+c-10);
	if (d<10)putchar('0'+d);else putchar('A'+d-10);
	puts("");
}

void write(int pos,int val)
{
	val%=MAX;
	save[pos]=val%256;
	save[pos+1]=val/256;
}

int main()
{
	init();
	for (step=cnt=1;cnt<=LIM;step++,cnt++)
	{
		if (ins[step].type==1)continue;
		if (ins[step].type==2)break;
		if (ins[step].type==3)
		{
			if (ins[step].ta==0)
			{
				if (ins[step].a>=0)ex(ins[step].a);
				else ex(x[-ins[step].a]);
				continue;
			}
			if (ins[step].a>=0)
			{
				if (re(ins[step].a)||re(ins[step].a+1))
				{
					puts("ACCESS_VIOLATION");
					break;
				}
				ex(save[ins[step].a]+save[ins[step].a+1]*256);
			}
			else
			{
				if (re(x[-ins[step].a])||re(x[-ins[step].a]+1))
				{
					puts("ACCESS_VIOLATION");
					break;
				}
				ex(save[x[-ins[step].a]]+save[x[-ins[step].a]+1]*256);
			}
			continue;
		}
		if (ins[step].type==4)
		{
			if (ins[step].ta==0)
			{
				if (ins[step].tb==0)
				{
					if (ins[step].b>=0)x[-ins[step].a]+=ins[step].b,x[-ins[step].a]%=MAX;
					else x[-ins[step].a]+=x[-ins[step].b],x[-ins[step].a]%=MAX;
					continue;
				}
				if (ins[step].b>=0)
				{
					if (re(ins[step].b)||re(ins[step].b+1))
					{
						puts("ACCESS_VIOLATION");
						break;
					}
					x[-ins[step].a]+=save[ins[step].b]+save[ins[step].b+1]*256;
					x[-ins[step].a]%=MAX;
					continue;
				}
				if (re(x[-ins[step].b])||re(x[-ins[step].b]+1))
				{
					puts("ACCESS_VIOLATION");
					break;
				}
				x[-ins[step].a]+=save[x[-ins[step].b]]+save[x[-ins[step].b]+1]*256;
				x[-ins[step].a]%=MAX;
				continue;
			}
			if (ins[step].a>=0)
			{
				if (re(ins[step].a)||re(ins[step].a+1))
				{
					puts("ACCESS_VIOLATION");
					break;
				}
				if (ins[step].tb==0)
				{
					if (ins[step].b>=0)write(ins[step].a,save[ins[step].a]+save[ins[step].a+1]*256+ins[step].b);
					else write(ins[step].a,save[ins[step].a]+save[ins[step].a+1]*256+x[-ins[step].b]);
					continue;
				}
				if (ins[step].b>=0)
				{
					if (re(ins[step].b)||re(ins[step].b+1))
					{
						puts("ACCESS_VIOLATION");
						break;
					}
					write(ins[step].a,save[ins[step].a]+save[ins[step].a+1]*256+save[ins[step].b]+save[ins[step].b+1]*256);
					continue;
				}
				if (re(x[-ins[step].b])||re(x[-ins[step].b]+1))
				{
					puts("ACCESS_VIOLATION");
					break;
				}
				write(ins[step].a,save[ins[step].a]+save[ins[step].a+1]*256+save[x[-ins[step].b]]+save[x[-ins[step].b]+1]*256);
				continue;
			}
			if (re(x[-ins[step].a])||re(x[-ins[step].a]+1))
			{
				puts("ACCESS_VIOLATION");
				break;
			}
			if (ins[step].tb==0)
			{
				if (ins[step].b>=0)write(x[-ins[step].a],save[x[-ins[step].a]]+save[x[-ins[step].a]+1]*256+ins[step].b);
				else write(x[-ins[step].a],save[x[-ins[step].a]]+save[x[-ins[step].a]+1]*256+x[-ins[step].b]);
				continue;
			}
			if (ins[step].b>=0)
			{
				if (re(ins[step].b)||re(ins[step].b+1))
				{
					puts("ACCESS_VIOLATION");
					break;
				}
				write(x[-ins[step].a],save[x[-ins[step].a]]+save[x[-ins[step].a]+1]*256+save[ins[step].b]+save[ins[step].b+1]*256);
				continue;
			}
			if (re(x[-ins[step].b])||re(x[-ins[step].b]+1))
			{
				puts("ACCESS_VIOLATION");
				break;
			}
			write(x[-ins[step].a],save[x[-ins[step].a]]+save[x[-ins[step].a]+1]*256+save[x[-ins[step].b]]+save[x[-ins[step].b]+1]*256);
			continue;
		}
		if (ins[step].type==5)
		{
			if (ins[step].ta==0)
			{
				x[-ins[step].a]++;
				x[-ins[step].a]%=MAX;
				continue;
			}
			if (ins[step].a>=0)
			{
				if (re(ins[step].a)||re(ins[step].a+1))
				{
					puts("ACCESS_VIOLATION");
					break;
				}
				write(ins[step].a,save[ins[step].a]+save[ins[step].a+1]*256+1);
				continue;
			}
			if (re(x[-ins[step].a])||re(x[-ins[step].a]+1))
			{
				puts("ACCESS_VIOLATION");
				break;
			}
			write(x[-ins[step].a],save[x[-ins[step].a]]+save[x[-ins[step].a]+1]*256+1);
			continue;
		}
		if (ins[step].type==6)
		{
			if (ins[step].ta==0)
			{
				if (ins[step].tb==0)
				{
					if (ins[step].b>=0)x[-ins[step].a]=ins[step].b,x[-ins[step].a]%=MAX;
					else x[-ins[step].a]=x[-ins[step].b],x[-ins[step].a]%=MAX;
					continue;
				}
				if (ins[step].b>=0)
				{
					if (re(ins[step].b)||re(ins[step].b+1))
					{
						puts("ACCESS_VIOLATION");
						break;
					}
					x[-ins[step].a]=save[ins[step].b]+save[ins[step].b+1]*256;
					x[-ins[step].a]%=MAX;
					continue;
				}
				if (re(x[-ins[step].b])||re(x[-ins[step].b]+1))
				{
					puts("ACCESS_VIOLATION");
					break;
				}
				x[-ins[step].a]=save[x[-ins[step].b]]+save[x[-ins[step].b]+1]*256;
				x[-ins[step].a]%=MAX;
				continue;
			}
			if (ins[step].a>=0)
			{
				if (re(ins[step].a)||re(ins[step].a+1))
				{
					puts("ACCESS_VIOLATION");
					break;
				}
				if (ins[step].tb==0)
				{
					if (ins[step].b>=0)write(ins[step].a,ins[step].b);
					else write(ins[step].a,x[-ins[step].b]);
					continue;
				}
				if (ins[step].b>=0)
				{
					if (re(ins[step].b)||re(ins[step].b+1))
					{
						puts("ACCESS_VIOLATION");
						break;
					}
					write(ins[step].a,save[ins[step].b]+save[ins[step].b+1]*256);
					continue;
				}
				if (re(x[-ins[step].b])||re(x[-ins[step].b]+1))
				{
					puts("ACCESS_VIOLATION");
					break;
				}
				write(ins[step].a,save[x[-ins[step].b]]+save[x[-ins[step].b]+1]*256);
				continue;
			}
			if (re(x[-ins[step].a])||re(x[-ins[step].a]+1))
			{
				puts("ACCESS_VIOLATION");
				break;
			}
			if (ins[step].tb==0)
			{
				if (ins[step].b>=0)write(x[-ins[step].a],ins[step].b);
				else write(x[-ins[step].a],x[-ins[step].b]);
				continue;
			}
			if (ins[step].b>=0)
			{
				if (re(ins[step].b)||re(ins[step].b+1))
				{
					puts("ACCESS_VIOLATION");
					break;
				}
				write(x[-ins[step].a],save[ins[step].b]+save[ins[step].b+1]*256);
				continue;
			}
			if (re(x[-ins[step].b])||re(x[-ins[step].b]+1))
			{
				puts("ACCESS_VIOLATION");
				break;
			}
			write(x[-ins[step].a],save[x[-ins[step].b]]+save[x[-ins[step].b]+1]*256);
			continue;
		}
		if (ins[step].type==7)
		{
			flag=1;
			if (ins[step].ta==0)
			{
				if (ins[step].a>=0)cmpa=ins[step].a;
				else cmpa=x[-ins[step].a];
			}
			else
			{
				if (ins[step].a>=0)
				{
					if (re(ins[step].a)||re(ins[step].a+1))
					{
						puts("ACCESS_VIOLATION");
						break;
					}
					cmpa=save[ins[step].a]+save[ins[step].a+1]*256;
				}
				else
				{
					if (re(x[-ins[step].a])||re(x[-ins[step].a]+1))
					{
						puts("ACCESS_VIOLATION");
						break;
					}
					cmpa=save[x[-ins[step].a]]+save[x[-ins[step].a]+1]*256;
				}
			}
			if (ins[step].tb==0)
			{
				if (ins[step].b>=0)cmpb=ins[step].b;
				else cmpb=x[-ins[step].b];
			}
			else
			{
				if (ins[step].b>=0)
				{
					if (re(ins[step].b)||re(ins[step].b+1))
					{
						puts("ACCESS_VIOLATION");
						break;
					}
					cmpb=save[ins[step].b]+save[ins[step].b+1]*256;
				}
				else
				{
					if (re(x[-ins[step].b])||re(x[-ins[step].b]+1))
					{
						puts("ACCESS_VIOLATION");
						break;
					}
					cmpb=save[x[-ins[step].b]]+save[x[-ins[step].b]+1]*256;
				}
			}
			continue;
		}
		if (ins[step].type==8)
		{
			if (flag==0&&ins[step].jmp!=0)
			{
				puts("CMP_MISSING");
				break;
			}
			if (ins[step].ta==0)
			{
				if (ins[step].a>=0)tpx=ins[step].a;
				else tpx=x[-ins[step].a];
			}
			else
			{
				if (ins[step].a>=0)
				{
					if (re(ins[step].a)||re(ins[step].a+1))
					{
						puts("ACCESS_VIOLATION");
						break;
					}
					tpx=save[ins[step].a]+save[ins[step].a+1]*256;
				}
				else
				{
					if (re(x[-ins[step].a])||re(x[-ins[step].a]+1))
					{
						puts("ACCESS_VIOLATION");
						break;
					}
					tpx=save[x[-ins[step].a]]+save[x[-ins[step].a]+1]*256;
				}
			}
			if (ins[step].jmp==0)
			{
				if ((tpx<2)||(tpx>n))
				{
					puts("RUNTIME_ERROR");
					break;
				}
				step=tpx-1;
				continue;
			}
			if (ins[step].jmp==1)
			{
				if (!(cmpa>cmpb))continue;
				if ((tpx<2)||(tpx>n))
				{
					puts("RUNTIME_ERROR");
					break;
				}
				step=tpx-1;
				continue;
			}
			if (ins[step].jmp==2)
			{
				if (!(cmpa<cmpb))continue;
				if ((tpx<2)||(tpx>n))
				{
					puts("RUNTIME_ERROR");
					break;
				}
				step=tpx-1;
				continue;
			}
			if (ins[step].jmp==3)
			{
				if (!(cmpa==cmpb))continue;
				if ((tpx<2)||(tpx>n))
				{
					puts("RUNTIME_ERROR");
					break;
				}
				step=tpx-1;
				continue;
			}
			if (ins[step].jmp==4)
			{
				if (!(cmpa<=cmpb))continue;
				if ((tpx<2)||(tpx>n))
				{
					puts("RUNTIME_ERROR");
					break;
				}
				step=tpx-1;
				continue;
			}
			if (ins[step].jmp==5)
			{
				if (!(cmpa>=cmpb))continue;
				if ((tpx<2)||(tpx>n))
				{
					puts("RUNTIME_ERROR");
					break;
				}
				step=tpx-1;
				continue;
			}
			if (ins[step].jmp==6)
			{
				if (!(cmpa!=cmpb))continue;
				if ((tpx<2)||(tpx>n))
				{
					puts("RUNTIME_ERROR");
					break;
				}
				step=tpx-1;
				continue;
			}
		}
	}
	if (cnt>LIM)puts("TLE");
	return 0;
}
