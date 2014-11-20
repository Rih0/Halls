// #include <iostream>
// #include <cstdlib>
// #include <algorithm>
// #include <cstdio>
// using namespace std;
// int data[10];

const int MAXSN = 201111;
const int INF = 0x7f7f7f7f;
struct node
{
    static node * NULLS;
    node *l,*r,*fa;
    int cnt;
    int val;
    int mins;
    int adder,rev;

    node(){
        val = adder = rev = 0;
        cnt = 0;                // 与下面的不同，此处必须为0,为了NULLS
        mins = INF;
    }
    void flip(){
        if(this != NULLS){
            swap(l,r);
            rev = !rev;
        }
    }
    void add(int num){
        if(this != NULLS){
            val += num;
            mins += num;
            adder += num;
        }
    }
    void pushdown(){
        if(this == NULLS) return;
        if(rev)
        {
            l->flip(),r->flip();
            rev = 0;
        }
        if(adder)
        {
            l->add(adder),r->add(adder);
            adder = 0;
        }
    }
    void update(){
        cnt = l->cnt + r->cnt + 1;
        mins = min(l->mins,r->mins);
        mins = min(mins,val);
    }
};
node * node::NULLS = new node;
node * NULLS = node::NULLS;
#define itvhead head->r->l

struct splaytree
{
    node * head;
    node memstack[MAXSN];
    int memp;
    inline node * NEWNODE(node * fa,int val) // 保证在不需要update时，值全部正确
    {
        node * p = &memstack[++memp];
        p->l = p->r = NULLS;
        p->fa = fa;
        p->cnt = 1;             // 必须设为1
        p->rev = p->adder = 0;
        p->val = p->mins = val;
        return p;
    }
    void init()
    {
        head = NEWNODE(NULLS,INF);
        head->r = NEWNODE(head,INF);
        head->r->update();
        head->update();
    }
    void clear(){
        memp = 0;
        init();
    }
    void routate(node * p){
        node * up=p->fa;
        up->pushdown(),p->pushdown();
        if(up==head)
        head=p;
        else
        {
            if(up->fa->r==up)
            up->fa->r=p;
            else
            up->fa->l=p;
        }
        p->fa=up->fa,up->fa=p;
        if(up->l==p)
        up->l=p->r,p->r->fa=up,p->r=up;
        else
        up->r=p->l,p->l->fa=up,p->l=up;
        up->update();
        p->update();
    }
    void splay(node * p,node * to){
        p->pushdown();
        while(p->fa!=to&&p->fa->fa!=to)
        {
            node * up=p->fa;
            if((up->fa->l==up&&up->l==p)||(up->fa->r==up&&up->r==p))
            {
                routate(up);
                routate(p);
            }
            else
            routate(p),routate(p);
        }
        if(p->fa!=to)
        routate(p);
        p->update();
    }
    node * FindK(node * p,int k){
        while(p!=NULLS){
            p->pushdown();
            if(p->l->cnt+1==k)
            return p;
            else if(p->l->cnt>=k)
            p=p->l;
            else
            k-=(p->l->cnt+1),p=p->r;
        }
        return NULLS;
    }
    int rank(int num){//对于不存在的数字，返回如果插入他后，他的rank
        citv(1,head->cnt-2);
        int ans=0;
        node * p = itvhead;
        while(p!=NULLS){
            p->pushdown();
            if(num>p->val)
            ans+=p->l->cnt+1,p=p->r;
            else if(num<p->val)
            p=p->l;
            else
            return p->l->cnt+1+ans;
        }
        return ans+1;
    }
    void citv(int a,int b){
        //此处为题意中需要被放置于head->r->l的区间
        node * p1=FindK(head,a);//-1+1
        node * p2=FindK(head,b+2);//+1+1
        splay(p1,NULLS);
        splay(p2,head);
    }
    void insert(int pos,int val) // 如果是有序表，则需要自己获取pos的位置，使用rank函数
    {
        citv(pos+1,pos);
        head->r->l = NEWNODE(head->r,val);
        head->r->update();
        head->update();
    }
    node * delitv(){
        node * tmp = itvhead;
        itvhead=NULLS;
        tmp->fa = NULLS;        // 切掉到父亲的链接
        head->r->update();
        head->update();
        return tmp;
    }
    void delnum(int num){//删除掉指定的数字，请确保其存在
        int ranks=rank(num);
        citv(ranks,ranks);
        delitv();
    }
    void cut(int a,int b,int c){//将[a,b]位置的内容剪切到[c,c+1)中间
        citv(a,b);
        node * temp = delitv();
        citv(c+1,c);
        itvhead = temp;
        temp->fa = head->r; //切记更新父指针
        head->r->update();
        head->update();
    }
    void flip(int a,int b){ //翻转[a,b]区间
        citv(a,b);
        itvhead->flip();
        head->r->update();
        head->update();
    }
    void do_build(node  * &p,int beg,int end,node * fa)
    {
        if(beg == end)
        {
            p = NEWNODE(fa,data[beg]);
            p->update();
            return ;
        }
        int mid = (beg + end) >> 1;
        p = NEWNODE(fa,data[mid]);
        if(beg <= mid - 1) do_build(p->l,beg,mid-1,p);
        if(end >= mid + 1) do_build(p->r,mid+1,end,p);
        p->update();
    }
    void build(int beg,int end) // 一颗完全平衡树
    {
        citv(1,0);// citv(k+1,k)区间代表把k位置右边的“真空”位置放在itvhead中
        do_build(head->r->l,beg,end,head->r);
    }
    void show(node * p){
        if(p == NULLS)
        return ;
        p->pushdown();
        show(p->l);
        printf("%d ",p->val);
        show(p->r);
    }
};
splaytree splay;