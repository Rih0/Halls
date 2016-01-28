#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;
#define NULLS &EMP
const int MAXN=101000;
struct Edge
{
	int num;
	int len;
	Edge * next;
};
Edge Ehead[MAXN];
Edge Edata[MAXN*2];
int Edatap;
char str[1231];
void addit(int &a,int & b,int & c)
{
	Edge * temp=Ehead[a].next;
	Edge * p=&Edata[++Edatap];
	Ehead[a].next=p,p->next=temp;
	p->num=b,p->len=c;
}
int T;
int N;
int a,b,c;
int Fa[MAXN];
int Val[MAXN];
bool vis[MAXN];
struct node
{
	int num;
	int maxs;
	node * l, * r;
	node * fa,* Pfa;
};
node EMP;
node data[MAXN*2];
int datap;
node * ToNode[MAXN];
node * NEWNODE(int num)
{
    node * p=&data[++datap];
	p->num=num,p->maxs=num;
	p->l=p->r=p->fa=p->Pfa=NULLS;
	return p;
}
int E[MAXN][2];
void update(node * p)
{
	if(p->l->maxs>p->r->maxs)
	p->maxs=p->l->maxs;
	else
	p->maxs=p->r->maxs;
	if(p->maxs<p->num)
	p->maxs=p->num;
}
void  routate(node * p)
{
	node * up=p->fa;
	if(up->fa==NULLS)
	p->Pfa=up->Pfa,up->Pfa=NULLS;
	else
	{
		if(up->fa->l==up)
		up->fa->l=p;
		else
		up->fa->r=p;
	}
	p->fa=up->fa;
	up->fa=p;
	if(up->l==p)
	{
		up->l=p->r;
		p->r->fa=up;
		p->r=up;
	}
	else
	{
		up->r=p->l;
		p->l->fa=up;
		p->l=up;
	}
	update(up);
}
void Splay(node * p)
{
	while(p->fa!=NULLS&&p->fa->fa!=NULLS)
	{
		if((p->fa->l==p&&p->fa->fa->l==p->fa)||(p->fa->r==p&&p->fa->fa->r==p->fa))
		routate(p->fa),routate(p);
		else
		routate(p),routate(p);
	}
	if(p->fa!=NULLS)
	routate(p);
	update(p);
}
void Access(node * p)
{
	node * x=p;
	node * y=NULLS;
	while(x!=NULLS)
	{
		Splay(x);
		x->r->Pfa=x,x->r->fa=NULLS;
		x->r=y;
		y->Pfa=NULLS,y->fa=x;
		y=x;
		x=y->Pfa;
	}
	Splay(p);
}
void dfs(int now)
{
	vis[now]=1;
	ToNode[now]=NEWNODE(Val[now]);
	ToNode[now]->Pfa=ToNode[Fa[now]];
	for(Edge * p=Ehead[now].next;p;p=p->next)
	{
		if(!vis[p->num])
		{
			Fa[p->num]=now;
			Val[p->num]=p->len;
			dfs(p->num);
		}
	}
}
int Qit(int& a,int &b)
{
	int maxs=-99999999;
	Access(ToNode[a]);
	node * x=ToNode[b];
	Splay(x);
	while(x->Pfa!=NULLS)
	{
		if(x->l->maxs>maxs)
		maxs=x->l->maxs;
		if(x->num>maxs)
		maxs=x->num;
		x=x->Pfa;
		Splay(x);
	}
	if(x->r->maxs>maxs)
	maxs=x->r->maxs;
	Access(ToNode[b]);
	return maxs;
}
void Cit(int& p,int &val)
{
	ToNode[p]->num=b;
	update(ToNode[p]);
	Splay(ToNode[p]);
}
void clear()
{
	Edatap=0,datap=0;
	memset(Ehead,0,sizeof(Ehead));
	memset(vis,0,sizeof(vis));
	memset(Fa,0,sizeof(Fa));
	memset(ToNode,0,sizeof(ToNode));
}
int x,y;
void work()
{
	ToNode[0]=NULLS;
	scanf("%d",&N);
	for(int i=1;i<N;i++)
	{
		scanf("%d%d%d",&a,&b,&c);
		addit(a,b,c);
		addit(b,a,c);
		E[i][0]=a,E[i][1]=b;
	}
	dfs(1);
	while(1)
	{
		scanf("%s",&str[1]);
		if(str[1]=='D')
		break;
		scanf("%d%d",&a,&b);
		if(str[1]=='Q')
		printf("%d\n",Qit(a,b));
		else if(str[1]=='C')
		{
            x=E[a][0];
			y=E[a][1];
			if(Fa[x]==y)
			Cit(x,b);
			else
			Cit(y,b);
		}
	}
	clear();
}
int main()
{
	//freopen("data.in","r",stdin);
	//freopen("dataLCT.out","w",stdout);
	scanf("%d",&T);
	//cerr<<T<<endl;
	for(int i=1;i<=T;i++)
	work();
	return 0;
}

