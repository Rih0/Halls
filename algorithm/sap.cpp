#include<iostream>
#include<cstring>
#include<cstdlib>
#include<cstdio>
#include<map>
#include<algorithm>
#include<cmath>
using namespace std;

//------------邻接表----------------------//
const int MAXN=201;//定义最大点数和边数
const int MAXM=201;
const int INF=0x7fffffff;
struct node
{
	int num,rest;//添加需要参数
	node * next;
	node * back;
};
node data[MAXM*3];
node head[MAXN];
int datap;
void Ginit()
{
	datap=0;
	memset(head,0,sizeof(head));
}
node * addE(int a,int b,int flow)//根据参数修改代码
{
	node * temp=head[a].next;
	node * p=&data[++datap];
	p->num=b,p->rest=flow,p->next=temp;
	head[a].next=p;
	return p;
}
//----------网络流sap-------------------//
void addit(int &a,int &b,int &c)//网络流特有加边
{
	node * p1=addE(a,b,c);
	node * p2=addE(b,a,0);
	p1->back=p2,p2->back=p1;
}
struct NetFlow//无需修改，仅仅需要自行处理建图部分
{
	int vd[MAXN];
	int d[MAXN];
	int S,T,N;
	int aug(int num,int allflow)
	{
		if(num==T)
		return allflow;
		int flow=allflow;
		int toflow,flowed;
		for(node * p=head[num].next;p;p=p->next)
		{
			if(p->rest&&d[p->num]==d[num]-1)
			{
				toflow=min(flow,p->rest);
				flowed=aug(p->num,toflow);
				flow-=flowed;
				p->rest-=flowed,p->back->rest+=flowed;
				if(flow==0)
				break;
				if(d[S]>=N)
				return allflow-flow;
			}
		}
		if(flow==allflow)
		{
			vd[d[num]]--;
			if(vd[d[num]]==0)
			d[S]=N;
			d[num]++;
			vd[d[num]]++;
		}
		return allflow-flow;
	}
	int sap(int beg,int end,int n)
	{
		S=beg,T=end,N=n;
		memset(d,0,sizeof(d));
		memset(vd,0,sizeof(vd));
		int ans=0;
		vd[S]=N;
		while(d[S]<N)
		ans+=aug(S,INF);
		return ans;
	}
}netflow;

//一下为题目特有
int N,M;
int a,b,c;
int main()
{
	while(scanf("%d",&M)!=EOF)
	{
		scanf("%d",&N);
		for(int i=1;i<=M;i++)
		{
			scanf("%d%d%d",&a,&b,&c);
			addit(a,b,c);
		}
		printf("%d\n",netflow.sap(1,N,N));
		Ginit();
	}
	return 0;
}