#define L(i) (i<<1)
#define R(i) ((i<<1)+1)
struct node
{
    int beg,end;

    int amax;
    int lmax,rmax;
    bool emp;

    int flag;
};
node Tree[MAXN*4+1];

int max(const int a,const int b,const int c)
{
    return max(max(a,b),c);
}
void update(int p)
{
    if(Tree[L(p)].emp)
    Tree[p].lmax = Tree[R(p)].lmax + Tree[L(p)].end - Tree[L(p)].beg;
    else
    Tree[p].lmax = Tree[L(p)].lmax;
    if(Tree[R(p)].emp)
    Tree[p].rmax = Tree[L(p)].rmax + Tree[R(p)].end - Tree[R(p)].beg;
    else
    Tree[p].rmax = Tree[R(p)].rmax;
    Tree[p].amax = max(Tree[L(p)].rmax + Tree[R(p)].lmax,Tree[L(p)].amax
        ,Tree[R(p)].amax);
    Tree[p].emp = Tree[L(p)].emp&&Tree[R(p)].emp;
}
void cit(int p,int opt)
{
    if(opt == 1)
    {
        Tree[p].emp = 1;
        Tree[p].amax = Tree[p].lmax = Tree[p].rmax = Tree[p].end - Tree[p].beg;
        Tree[p].flag = 1; // 覆盖性的操作
    }
    if(opt == 2)
    {
        Tree[p].emp = 0;
        Tree[p].amax = Tree[p].lmax = Tree[p].rmax = 0;
        Tree[p].flag = 2;
    }
}
void pushdown(int p)
{
    if(Tree[p].beg + 1 == Tree[p].end)
    return ;
    if(Tree[p].flag == 1)
    {
        cit(L(p),1),cit(R(p),1);
    }
    else if(Tree[p].flag == 2)
    {
        cit(L(p),2),cit(R(p),2);
    }
    Tree[p].flag = 0;//清楚标记
}
void built(int p,int beg,int end)
{
    Tree[p].beg=beg,Tree[p].end=end;
    if(beg+1==end)
    {
        Tree[p].amax=Tree[p].lmax=Tree[p].rmax = 1;
        Tree[p].emp = 1;
        return ;
    }
    int mid=(beg+end)>>1;
    built(p<<1,beg,mid);
    built((p<<1)+1,mid,end);
    update(p);
}
void change(int p,int beg,int end,int opt)
{
    pushdown(p);
    if(Tree[p].beg==beg&&Tree[p].end==end)
    {
        cit(p,opt);
        return;
    }
    int mid=(Tree[p].beg+Tree[p].end)>>1;
    if(end<=mid)
    change(p<<1,beg,end,opt);
    else if(beg>=mid)
    change((p<<1)+1,beg,end,opt);
    else
    change(p<<1,beg,mid,opt),change((p<<1)+1,mid,end,opt);
    update(p);
}