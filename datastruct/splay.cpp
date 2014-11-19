const int MAXSN=MAXN+100;//最大点数!!!!!
class spnode
{
public:
    static spnode * NULLS;
    spnode * l,*r,*fa;
    int cnt;

    /*data member*/
    bool flag_rev;
    int val;
    spnode(){
        cnt=val=0;
        flag_rev = 0;
    }
    void flip(){
        if(this != NULLS)
        {
            swap(l,r);
            flag_rev = !flag_rev;
            /*modify method*/
            //------example--------
            // sum+=ad*cnt;
            // val+=ad;
            // adds+=ad;
            //---记得标记之间的传递----
        }
    }
    void pushdown(){//传递标记操作
        /*pushdown method*/
        if(flag_rev)
        {
            l->flip(),r->flip();
            flag_rev = 0;
        }
    }
    void update(){
        /*update method*/
        cnt=l->cnt+r->cnt+1;
    }
};
spnode * spnode::NULLS = new spnode;
#define NULLS spnode::NULLS
#define itvhead head->r->l
template<class node>
class splaytree
{
public:
    node * head;
    node memstack[MAXSN];
    int memstackp;
    int flag_show;
    inline node * NEWNODE(node * fa){
        node * p=&memstack[++memstackp];
        p->l=p->r=NULLS;
        p->fa=fa;
        p->cnt = p->val = p->flag_rev = 0;
        return p;
    }
    splaytree(){
        head=NEWNODE(NULLS);
        head->r=NEWNODE(head);
        head->r->update();
        head->update();
    }
    void clear(){
        memstackp = 0;
        splaytree();
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
        pf("%d ",p->val);
        show(p->r);
    }
};
splaytree<spnode> splay;