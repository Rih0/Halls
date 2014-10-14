#include <iostream>
#include <fstream>
#include <sstream>
#include <utility>
#include <vector>
#include <list>
#include <string>
#include <stack>
#include <queue>
#include <deque>
#include <set>
#include <map>
#include <algorithm>
#include <functional>
#include <numeric>
#include <bitset>
#include <complex>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <climits>
using namespace std;

#define ft(i,a,b) for (int i=(a);i<=(b);++i)
#define fdt(i,a,b) for (int i=(a);i>=b;--i)
#define feach(arr,e) for (vector<piii>::itr e=(arr).begin();e!=(arr).end();++e)
#define fsubset(subset,set) for (int subset=set&(set-1);subset;subset=(subset-1)&set)
#define fl(x,y) memset((x),char(y),sizeof(x))
#define clr(x) fl(x,char(0))
#define pb push_back
#define mp make_pair
#define x first
#define y second
#define sz(x) (int((x).size()))
#define all(x) (x).begin(),(x).end()
#define srt(x) sort(all(x))
#define uniq(x) srt(x),(x).erase(unique(all(x)),x.end());
#define present(c,x) ((c).find(x) != (c).end()) 
#define cpresent(c,x) (find(all(c),x) != (c).end())
#define pr pair
#define que queue
#define prq priority_queue
#define itr iterator
#define sf scanf
#define pf printf
#define pdb(prcs,x) printf("%."#prcs"f",(abs(x)<1e-##prcs)?0.0:x)
#define input(in) freopen(in,"r",stdin)
#define output(out) freopen(out,"w",stdout)

#define lowbit(i) (i&(-i))

typedef long long int LL;
typedef pr<int,int> pii;
typedef pr<LL,LL> pll;
typedef pr<double,double> pdd;
typedef pr<string,int> psi;
typedef map<int,int> mii;
typedef map<string,int> msi;
typedef map<char,int> mci;
typedef que<int> qi;
typedef prq<int> pqi;
typedef vector<int> veci;
typedef vector<bool> vecb;
typedef vector<string> vecs;
typedef vector<double> vecdb;

const int oo=(~0u)>>1;
const LL lloo=(~0ull)>>1;
const int INF = 0x7f7f7f7f;
const double dboo=1e+20;
const double eps=1e-8;
const double pi=acos(-1.0);
const int MOD=1000000007;

const int MAXN = 11111;

int T;
int N;
int a,b,c;
typedef pr<pii,int> piii;
vector<piii> maps[MAXN];
bool vis[MAXN];
int nodeval[MAXN];
int fa[MAXN];
int eto[MAXN];

inline void get_max(int &a,const int b)
{
    if(b > a)
    a = b;
}

struct node
{
    node * l, *r;
    node * fa,* path;
    bool neg;
    int val,maxs,mins;
    static node * NULLS;
    void push_down(){
        if(neg){
            neg = 0;
            l->do_neg();
            r->do_neg();
        }
    }
    void update(){
        maxs = max(l->maxs,r->maxs);
        maxs = max(maxs,val);
        mins = min(l->mins,r->mins);
        mins = min(mins,val);
    }
    void do_neg(){
        if(this == NULLS){
            return ;
        }
        neg = !neg;
        val = - val;
        int oldmax = maxs;
        maxs = -mins;
        mins = -oldmax;
    }
};
node EMP;
node * node::NULLS = (&EMP);
node * NULLS = node::NULLS;
node data[MAXN*2];
int datap;
node * tonode[MAXN];

node * NEWNODE(int val)
{
    node * p = &data[++datap];
    p->val = p->maxs = p->mins = val;
    p->l = p->r = p->fa = p->path = NULLS;
    p->neg = 0;                 // depends on individual problem
    return p;
}
void lct_init()
{
    EMP.maxs = EMP.val = -INF;
    EMP.mins = INF;
}
void rotate(node * p)
{
    node * up = p->fa;
    up->push_down(),p->push_down();
    // set upper inf
    if (up->fa == NULLS) {
        p->path = up->path;
        up->path = NULLS;
    } else {
        if (up->fa->l == up) {
            up->fa->l = p;
        } else {
            up->fa->r = p;
        }
    }
    p->fa = up->fa;
    up->fa = p;
    if (up->l == p) {
        up->l = p->r;
        p->r->fa = up;
        p->r = up;
    } else {
        up->r = p->l;
        p->l->fa = up;
        p->l = up;
    }
    up->update();
    p->update();
}
#define SAMELINE(p,chd) (p->fa->fa->chd == p->fa && p->fa->chd == p)
void splay(node * p)
{
    
    if (p == NULLS)
    return ;
    p->push_down();
    while(p->fa != NULLS && p->fa->fa != NULLS){
        if (SAMELINE(p,l) && SAMELINE(p,r)) {
            rotate(p->fa),rotate(p);
        } else {
            rotate(p),rotate(p);
        }
    }
    if(p->fa != NULLS){
        rotate(p);
    }
    p->update();
}
void access(node * p)
{
    node * x = p;
    node * y = NULLS;
    while(x != NULLS){
        splay(x);                           // 旋转到根
        x->r->path = x, x->r->fa = NULLS;   // 切断右儿子(deeper)
        x->r = y;                           // 等于刚才切开的
        y->path = NULLS,y->fa = x;          // 刚才切的也接上
        x->update();                        // 更新
        y = x;                              // 迭代
        x = x->path;                        // 迭代
    }
    splay(p);
}
node * lca(node * x, node * y)
{
    access(x);                  // 把lca加入重链
    splay(y);                   //
    node * rt = y->path;
    while(rt != NULLS){
        y = rt;
        splay(y);
        rt = y->path;
    }
    return y;                   // 最后lca是y
}
// 所有的求解最优解的过程，都在以上求lca的基础上进行变化
// 请注意包括lca点的值，在while循环中需要考察

void dfs(int now)
{
    vis[now] = 1;
    feach(maps[now],p){
        int to = p->x.x;
        int len = p->x.y;
        int eid = p->y;
        if(!vis[to])
        {
            nodeval[to] = len;
            fa[to] = now;
            eto[eid] = to;
            dfs(to);
        }
    }
}
void built()
{
    for (int i = 1; i <= N; ++i)
    {

        tonode[i] = NEWNODE(nodeval[i]);
    }
    for (int i = 1; i <= N; ++i)
    {
        if(fa[i] != 0)
        {
            tonode[i]->path = tonode[fa[i]];
        }
    }
}
void init(){
    for (int i = 1; i < N; ++i)
    {
        scanf("%d%d%d",&a,&b,&c);
        maps[a].pb(piii(pii(b,c),i));
        maps[b].pb(piii(pii(a,c),i));
    }
    dfs(1);
    built();
}
// void query(node * x,node * y)
// {
//     access(x);
//     splay(y);
//     node * rt = y->path;
//     int maxs = -INF;
//     while(rt != NULLS){
//         get_max(maxs,y->val);
//         get_max(maxs,y->l->maxs);
//         y = rt;
//         splay(y);
//         rt = y->path;
//     }
//     get_max(maxs,y->r->maxs);
//     // 不处理y->val是因为val on the edges
//     printf("%d\n",maxs);
// }
void query(node * x, node * y)
{
    node * rt;
    access(x);
    for (rt = y, y = NULLS; rt != NULLS; y = rt, rt = rt->path)
    {
        splay(rt);
        if(rt->path == NULLS){
            printf("%d\n",max(rt->r->maxs,y->maxs));
        }
        rt->r->path = rt, rt->r->fa = NULLS;   // 切断右儿子(deeper)
        rt->r = y;                           // 等于刚才切开的
        y->path = NULLS,y->fa = rt;          // 刚才切的也接上
        rt->update();                        // 更新
    }
}
void change(node * p, int val)
{
    splay(p);
    p->val = val;
    p->update();
}
void negpath(node * x , node * y)
{
    node * rt;
    access(x);
    for (rt = y, y = NULLS; rt != NULLS; y = rt, rt = rt->path)
    {
        splay(rt);
        if(rt->path == NULLS){
            rt->r->do_neg(),y->do_neg();
        }
        rt->r->path = rt, rt->r->fa = NULLS;   // 切断右儿子(deeper)
        rt->r = y;                           // 等于刚才切开的
        y->path = NULLS,y->fa = rt;          // 刚才切的也接上
        rt->update();                        // 更新
    }
}
void clear(){
    for (int i = 0; i < MAXN; ++i)
    {
        maps[i].clear();
    }
    clr(vis);
    clr(nodeval);
    clr(fa);
    clr(eto);
    datap = 0;
}
char str[MAXN];
int main(int argc, char *argv[])
{
    lct_init();
    scanf("%d",&T);
    ft(tt,1,T){
        scanf("%d",&N);
        init();
        while(1){
            scanf("%s",str + 1);
            if(str[1] == 'Q'){
                scanf("%d%d",&a,&b);
                query(tonode[a],tonode[b]);
            } else if (str[1] == 'C') {
                scanf("%d%d",&a,&b);
                change(tonode[eto[a]],b);
            } else if (str[1] == 'N') {
                scanf("%d%d",&a,&b);
                negpath(tonode[a],tonode[b]);
            } else {
                break;
            }
        }
        clear();
    }
    return 0;
}