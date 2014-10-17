// poj wedding
#include<iostream>
#include <cstdio>
#include <cstring>
#include<cmath>
#include<algorithm>
using namespace std;
const int MAXN=1000;
int N,M,N2;
int a,c;
char b,d;
int G[MAXN],B[MAXN],Same[MAXN];
struct node
{
	int num;
	node * next;
};
node data[MAXN*100];
int datap;
node head[MAXN];
int DFN[MAXN],Low[MAXN],Dp;
int stack[MAXN],stap,in[MAXN];
int Cor[MAXN],Corp;
node head2[MAXN];
int Ru[MAXN],Db[MAXN];

void addE(int &a,int &b)
{
	node * p=&data[++datap];
	p->num=b,p->next=head[a].next;
	head[a].next=p;
}
void addE2(int &a,int &b)
{
	node * p=&data[++datap];
	p->num=b,p->next=head2[a].next;
	head2[a].next=p;
	Ru[b]++;
}
void addxorE(int &a,int &b)
{
	addE(a,Same[b]);
	addE(b,Same[a]);
}
void Tarjan(int num)
{
	DFN[num]=Low[num]=++Dp;
	stack[++stap]=num,in[num]=1;
	for(node * p=head[num].next;p;p=p->next)
	{
		if(!DFN[p->num])
		{
			Tarjan(p->num);
			Low[num]=min(Low[p->num],Low[num]);
		}
		else if(in[p->num])
        Low[num]=min(Low[num],DFN[p->num]);
	}
	if(Low[num]>=DFN[num])
	{
		Corp++;
		Db[Corp]=num;
		do
		{
			in[stack[stap]]=0;
			Cor[stack[stap--]]=Corp;
		}while(stack[stap+1]!=num);
	}
}
bool Wrong()
{
	for(int i=1;i<=N;i++)
	if(Cor[G[i]]==Cor[B[i]])
	return 1;
	return 0;
}
int que[MAXN];
int fir,last;
int Xu[MAXN];
int Xup;
void Tuop()
{
	while(fir!=last) {
		int &now=que[++last];
		Xu[++Xup]=now;
		for(node * p=head2[now].next;p;p=p->next){
			Ru[p->num]--;
			if(!Ru[p->num])
			que[++fir]=p->num;
		}
	}
}
int del[MAXN],cho[MAXN];
void Todel(int num)
{
	del[num]=1;
	for(node *p=head2[num].next;p;p=p->next)
	Todel(p->num);
}
int main()
{
	scanf("%d%d",&N,&M);
	N2=N*2;
	for(int i=1;i<=N;i++)
	G[i]=i,B[i]=i+N,Same[i]=i+N,Same[i+N]=i;

	for(int i=1;i<=M;i++)
	{
		scanf("%d%c%d%c",&a,&b,&c,&d);
		a++,c++;
		if(b=='h'&&d=='h')
		addxorE(B[a],B[c]);
		else if(b=='h'&&d=='w')
		addxorE(B[a],G[c]);
		else if(b=='w'&&d=='h')
		addxorE(G[a],B[c]);
		else if(b=='w'&&d=='w')
		addxorE(G[a],G[c]);
	}
	addE(B[1],G[1]);
	for(int i=1;i<=N2;i++)
	if(!DFN[i])
	Tarjan(i);
	if(Wrong())
	printf("bad luck\n");
	else
	{
		for(int i=1;i<=N2;i++)
		for(node * p=head[i].next;p;p=p->next)
		{
			if(Cor[p->num]!=Cor[i])
			addE2(Cor[p->num],Cor[i]);
		}
		for(int i=1;i<=Corp;i++)
		if(!Ru[i])
		que[++fir]=i;
        // 先把0的都拿出来了
		Tuop();
		for(int i=1;i<=Corp;i++)
		cout<<Xu[i]<<" ";
		cout<<endl;
		for(int i=1;i<=Corp;i++)
		{
			int & now=Xu[i];
			if(!del[now])
			{
				cho[now]=1;
				Todel(Cor[Same[Db[i]]]);
			}
		}
		for(int i=2;i<=N;i++)
		{
			if(cho[Cor[G[i]]])
			printf("%dw ",i-1);
			else
			printf("%dh ",i-1);
		}
	}
	return 0;
}