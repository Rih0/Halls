/*
  POJ2396
  NetFlow with lower_bound , source-terminal.
  add fake-source and fake-terminal.
  possible solution algorithm not maxium one.
*/
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
using namespace std;


#define NEWNODE &data[++datap]
const int INF=99999999;
const int MAXN=500;
const int MAXM=500;
const int MAXC=MAXN*MAXM*2;
int N,M,C;
int S,T,tot,Ss,St;
struct node
{
	int num,rest;
	node * next,* back;
};
int d[MAXC];
int vd[MAXC];
node head[MAXC];
node data[MAXC*10];
int datap;
int Nin[MAXC];
int Nout[MAXC];
int Hto[MAXC];
int Lto[MAXC];
int Cellto[MAXN][MAXM];
int a,b,lim;
char c;
int hsum[MAXC];
int lsum[MAXC];
node * toe[MAXC];
int tote;
node * ans[MAXN][MAXM];
int Cmin[MAXN][MAXM];
int Cmax[MAXN][MAXM];
node * addit(int a,int b,int c)
{
	node * temp=head[a].next;
	node * p=NEWNODE;
	head[a].next=p,p->next=temp;
	p->num=b,p->rest=c;
	return p;
}
node * addE(int a,int b,int c,int d)//c上界，d下界
{
	Nout[a]+=d,Nin[b]+=d;       // 对于每个点，记录它的入值和出值
	node * p1=addit(a,b,c-d);
	node * p2=addit(b,a,0);
	p1->back=p2;
	p2->back=p1;
	return p1;
}
int aug(int num,int rest)
{
	if(num==St)
	return rest;
	int toflow=rest;
	int flowed;
	for(node * p=head[num].next;p;p=p->next)
	{
		if(p->rest)
		{
			if(d[p->num]==d[num]-1)
			{
				if(toflow<p->rest)
				flowed=aug(p->num,toflow);
				else
				flowed=aug(p->num,p->rest);
				toflow-=flowed;
				p->rest-=flowed;
				p->back->rest+=flowed;
				if(toflow==0)
				break;
				if(d[Ss]>=tot)
				return rest-toflow;
			}
		}
	}
	if(toflow==rest)
	{
		vd[d[num]]--;
		if(vd[d[num]]==0)
		d[Ss]=tot;
		d[num]++;
		vd[d[num]]++;
	}
	return rest-toflow;
}
int Sap()
{
	memset(d,0,sizeof(d));
	memset(vd,0,sizeof(vd));
	int ans=0;
	vd[0]=tot;
	while(d[Ss]<tot)
	ans+=aug(Ss,INF);
	return ans;
}
void Maket()
{
	for(int i=1;i<=N;i++)
	for(int j=1;j<=M;j++)
	Cmin[i][j]=0,Cmax[i][j]=INF;
	int p=0;
	for(int i=1;i<=N;i++)
	for(int j=1;j<=M;j++)
	Cellto[i][j]=++p;
	for(int i=1;i<=N;i++)
	Hto[i]=++p;
	for(int i=1;i<=M;i++)
	Lto[i]=++p;
	S=0,T=p+1;
	Ss=T+1,St=T+2;
	tot=St+1;
    // 设置基本的点编号
}
void init()
{
	memset(Nin,0,sizeof(Nin));
	memset(Nout,0,sizeof(Nout));
	memset(head,0,sizeof(head));
	tote=0;
	datap=0;
	scanf("%d%d",&N,&M);
	Maket();                    // 设置基本编号
	for(int i=1;i<=N;i++)
	scanf("%d",&hsum[i]);
	for(int i=1;i<=M;i++)
	scanf("%d",&lsum[i]);       // 行和与列和
	scanf("%d",&C);             // 要求
	for(int i=1;i<=C;i++)
	{
		scanf("%d%d%s%d",&a,&b,&c,&lim);
		if(a==0&&b==0)
		{
			for(int i=1;i<=N;i++)
			for(int j=1;j<=M;j++)
			{
				int &Min=Cmin[i][j];
				int &Max=Cmax[i][j];
				if(c=='>')
				Min=max(lim+1,Min);
				else if(c=='=')
				Max=min(lim,Max),Min=max(lim,Min);
				else
				Max=min(lim-1,Max);
			}
		}
		else if(b==0)
		{
			for(int i=1;i<=M;i++)
			{
				int &Min=Cmin[a][i];
				int &Max=Cmax[a][i];
				if(c=='>')
				Min=max(lim+1,Min);
				else if(c=='=')
				Max=min(lim,Max),Min=max(lim,Min);
				else
				Max=min(lim-1,Max);
			}
		}
		else if(a==0)
		{
			for(int i=1;i<=N;i++)
			{
				int &Min=Cmin[i][b];
				int &Max=Cmax[i][b];
				if(c=='>')
				Min=max(lim+1,Min);
				else if(c=='=')
				Max=min(lim,Max),Min=max(lim,Min);
				else
				Max=min(lim-1,Max);
			}
		}
		else
		{
			int &Min=Cmin[a][b];
			int &Max=Cmax[a][b];
			if(c=='>')
			Min=max(lim+1,Min);
			else if(c=='=')
			Max=min(lim,Max),Min=max(lim,Min);
			else
			Max=min(lim-1,Max);
		}
	}
	for(int i=1;i<=N;i++)
	addE(S,Hto[i],hsum[i],hsum[i]);
    // 每行的要求
	for(int i=1;i<=N;i++)
	for(int j=1;j<=M;j++)
	addE(Hto[i],Cellto[i][j],INF,0);
    // 行到点的边
	for(int i=1;i<=N;i++)
	for(int j=1;j<=M;j++)
	ans[i][j]=addE(Cellto[i][j],Lto[j],Cmax[i][j],Cmin[i][j]);
    // 点到列的边
	for(int i=1;i<=M;i++)
	addE(Lto[i],T,lsum[i],lsum[i]);
    // 列到终点的边
	addE(T,S,INF,0);
    // 最后的
}
void built()
{
	for(int i=0;i<=T;i++)
	if(Nin[i]>Nout[i])
	addE(Ss,i,Nin[i]-Nout[i],0); // 如果in > out ， 连一天条从super source 到它的点
	else
	toe[++tote]=addE(i,St,Nout[i]-Nin[i],0); // 如果小于，它到super terminal 的边
}
bool check()
{
	for(node * p=head[Ss].next;p;p=p->next)
	if(p->rest)
	return 0;
	for(int i=1;i<=tote;i++)
	if(toe[i]->rest)
	return 0;
    // super source, terminal都必须是满流边
	return 1;
}
int Q;
int main()
{
	cin>>Q;
	for(int q=1;q<=Q;q++)
	{
		init();
		built();
		Sap();
		if(check())
		{
			for(int i=1;i<=N;i++,printf("\n"))
			{
				printf("%d",ans[i][1]->back->rest+Cmin[i][1]);
				for(int j=2;j<=M;j++)
				printf(" %d",ans[i][j]->back->rest+Cmin[i][j]);
			}
			printf("\n");
		}
		else
		printf("IMPOSSIBLE\n");
	}
	return 0;
}