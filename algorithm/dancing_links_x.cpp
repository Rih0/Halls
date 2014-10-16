/*
	POJ 3074 数独Dancing Links X
	代码重构后的版本
*/
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
#define NEWNODE (&data[++datap])
const int INF=9999999;
struct node
{
	node * l,*r,*u,*d,*back;
	int type;
};
int typeto[1000][3];
node * hang[10][10];
node * lie[10][10];
node * gong[10][10];
node * placed[10][10];
node * temp[100];
node * head;
node data[1000000];
int ans[10][10];
int datap;
int S[1000];
node * Hengadd(int num)//建立横向环
{
	node * temp=head->r;
	node * p=NEWNODE;
	p->u=p->d=p;
	head->r=p,p->r=temp;
	temp->l=p,p->l=head;
	p->type=num;
	return p;
}
node * Downadd(node * roots,int type)//建立纵向环
{
	S[roots->type]++;
	node * temp=roots->d;
	node * p=NEWNODE;
	roots->d=p,p->d=temp;
	temp->u=p,p->u=roots;
	p->back=roots,p->type=type;
	return p;
}
void headbuilt()//头建立
{
	int p=0;
	for(int i=1;i<=9;i++)
	for(int j=1;j<=9;j++)
	{
		placed[i][j]=Hengadd(++p);
		hang[i][j]=Hengadd(++p);
		lie[i][j]=Hengadd(++p);
		gong[i][j]=Hengadd(++p);
	}
}
void Chuan()
{
	for(int i=1;i<4;i++)
	temp[i]->r=temp[i+1],temp[i+1]->l=temp[i];
	temp[1]->l=temp[4],temp[4]->r=temp[1];
}
int GetG(int a,int b)//定位宫的位置
{
    return  ((a+2)/3-1)*3+((b+2)/3);
}
void built()
{
	int type=0;
	for(int i=1;i<=9;i++)	
	for(int j=1;j<=9;j++)
	for(int k=1;k<=9;k++)
	{
		type++;
		typeto[type][0]=k,typeto[type][1]=i,typeto[type][2]=j;
		temp[1]=Downadd(hang[i][k],type);
		temp[2]=Downadd(lie[j][k],type);
		temp[3]=Downadd(placed[i][j],type);
		temp[4]=Downadd(gong[GetG(i,j)][k],type);
		Chuan();
	}
}
void builtit()
{
	head=NEWNODE;
	head->l=head->r=head->u=head->d=head;
	headbuilt();
	built();
}
void Cover(node * p)
{
	p->l->r=p->r;
	p->r->l=p->l;
	for(node * now=p->d;now!=p;now=now->d)
		for(node * j=now->r;j!=now;j=j->r)
		S[j->back->type]--,j->u->d=j->d,j->d->u=j->u;
}
void Cancel(node * p)
{
	p->l->r=p;
	p->r->l=p;
	for(node * now=p->u;now!=p;now=now->u)
		for(node * j=now->l;j!=now;j=j->l)
		S[j->back->type]++,j->u->d=j,j->d->u=j;
}
void ChoseOne(int i,int j,int k)
{
	node * r=placed[i][j];
	Cover(r);
	for(node*  p=r->d;p!=r;p=p->d)
	{
		if(typeto[p->type][0]==k)
		{
			for(node * j=p->r;j!=p;j=j->r)
			Cover(j->back);
		}
	}
}
bool dfs(int dep)
{
	//cout<<dep<<endl;
	if(head->r==head)
	{
		for(int i=1;i<=9;i++)
		for(int j=1;j<=9;j++)
		printf("%d",ans[i][j]);
		printf("\n");
		return 1;
	}
	int min=INF;
	node * cho;
	for(node * p=head->r;p!=head;p=p->r)
	if(S[p->type]<min)
		min=S[p->type],cho=p;
	if(cho->u==cho)
	return 0;
	Cover(cho);
	for(node * p=cho->d;p!=cho;p=p->d)
	{
		int &x=typeto[ p->type][1];
		int &y=typeto[ p->type][2];
		int &k=typeto[ p->type][0];
		ans[x][y]=k;
		for(node * j=p->l;j!=p;j=j->l)
		Cover(j->back);
		bool flag=dfs(dep+1);
		if(flag)
		return 1;
		for(node * j=p->r;j!=p;j=j->r)
		Cancel(j->back);
		ans[x][y]=0;
	}
	Cancel(cho);
	return 0;
}
char str1[1000];
void clear()
{
	head=NULL;
	datap=0;
	memset(S,0,sizeof(S));
}
int main()
{
    while(scanf("%s",&str1[1])!=EOF)
    {
		if(str1[1]=='e'&&str1[2]=='n'&&str1[3]=='d')
		break;
		builtit();
        int p=1;
		for(int i=1;i<=9;i++)
        for(int j=1;j<=9;j++)                            
        {
			if(str1[p]!='.')
			{
                ans[i][j]=str1[p]-'0'; 
				ChoseOne(i,j,str1[p]-'0');
			}
			p++;
		}
		if(!dfs(1))
		printf("NO\n");
		clear();
    }
	return 0;
}