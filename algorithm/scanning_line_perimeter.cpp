const int MAXL=50111;
const int MAXN=50111;
const int PY=0;
struct node
{
    int beg,end;
    int sumlen;
    int cnt;
    bool lc,rc;// 统计区间个数
    int cover;//-1代表是杂色，0代表尚未被覆盖，>0个数代表覆盖次数
    int flag;
};
node tree[MAXL*4+100];
struct edge
{
    int x,y1,y2,flag;
};
edge shu[MAXN+100];
int shup;
void addone(int x,int y1,int y2,int flag)
{
    shu[++shup].x=x,shu[shup].y1=y1,shu[shup].y2=y2,shu[shup].flag=flag;
}
int cmp(const void * a,const void * b)
{
    if((*(edge *)a).x==(*(edge *)b).x)
    return (*(edge *)b).flag-(*(edge *)a).flag;
    return (*(edge *)a).x-(*(edge *)b).x;
}
void update(int p)
{
    tree[p].lc=tree[(p<<1)].lc;
    tree[p].rc=tree[(p<<1)+1].rc;
    tree[p].cnt=(tree[(p<<1)].cnt+tree[(p<<1)+1].cnt)-(tree[(p<<1)].rc&&tree[(p<<1)+1].lc);
    tree[p].sumlen=tree[(p<<1)].sumlen+tree[(p<<1)+1].sumlen;
    if(tree[p].beg!=tree[p].end-1)
    if(tree[(p<<1)].cover==tree[(p<<1)+1].cover)
    tree[p].cover=tree[(p<<1)].cover;
    else
    tree[p].cover=-1;
}
void Cit(int p,int num)
{
    tree[p].flag+=num;
    if(tree[p].cover!=-1)
    {
        tree[p].cover+=num;
        if(tree[p].cover>0)
        {
            tree[p].cnt=1;
            tree[p].lc=tree[p].rc=1;
            tree[p].sumlen=tree[p].end-tree[p].beg;
        }
        else
        {
            tree[p].cnt=0;
            tree[p].lc=tree[p].rc=0;
            tree[p].sumlen=0;
        }
    }
    else
    {
        Cit(p<<1,tree[p].flag),Cit((p<<1)+1,tree[p].flag);
        tree[p].flag=0;
        update(p);
    }
}
void PushDown(int p)
{
    if(tree[p].flag!=0)
    {
        if(tree[p].beg==tree[p].end-1)
        tree[p].flag=0;
        else
        {
            Cit(p<<1,tree[p].flag),Cit((p<<1)+1,tree[p].flag);
            tree[p].flag=0;
        }
    }
}
void change(int p,int beg,int end,int c)
{
    PushDown(p);
    if(tree[p].beg==beg&&tree[p].end==end)
    {
        Cit(p,c);
        return ;
    }
    int mid=(tree[p].beg+tree[p].end)>>1;
    if(end<=mid)
    change(p<<1,beg,end,c);
    else if(beg>=mid)
    change((p<<1)+1,beg,end,c);
    else
    {
        change(p<<1,beg,mid,c);
        change((p<<1)+1,mid,end,c);	
    }
    update(p);
}
void built(int p,int beg,int end)
{
    if(beg+1==end)
    {
        tree[p].beg=beg,tree[p].end=end;
        return ;
    }
    int mid=(beg+end)>>1;
    tree[p].beg=beg,tree[p].end=end;
    built(p<<1,beg,mid);
    built((p<<1)+1,mid,end);
    update(p);
}
int N;
int ax,ay,bx,by;
int ans;
int lastx,lasty;
int heng;
int lie;
int main()
{
    built(1,1,20010);
    scanf("%d",&N);
    for(int i=1;i<=N;i++)
    {
        scanf("%d%d%d%d",&ax,&ay,&bx,&by);
        ax+=PY;
        ay+=PY;
        bx+=PY;
        by+=PY;
        addone(ax,ay,by,1);
        addone(bx,ay,by,-1);
    }
    qsort(&shu[1],shup,sizeof(edge),cmp);
    lastx=shu[1].x;
    for(int i=1;i<=shup;i++)
    {
        ans+=(tree[1].cnt)*2*(shu[i].x-lastx);
        change(1,shu[i].y1,shu[i].y2,shu[i].flag);
        ans+=abs(tree[1].sumlen-lasty);
        lasty=tree[1].sumlen;
        lastx=shu[i].x;
    }
    printf("%d",ans);
    //	system("pause");
    return 0;
}