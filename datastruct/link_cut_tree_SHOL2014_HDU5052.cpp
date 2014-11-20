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
#define feach(arr,e) for (typeof((arr).begin()) e=(arr).begin();e!=(arr).end();++e)
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
const int INF = 0x3f3f3f3f;
const double dboo=1e+20;
const double eps=1e-8;
const double pi=acos(-1.0);
const int MOD=1000000007;
const int MAXN = 51111;

int T,N,Q;
int a,b,c;
struct node
{
    node * l, *r;
    node * fa,* path;
    int val;
    int maxs, mins;
    int mm,rmm;
    int flag;
    bool rev;
    static node * NULLS;
    void push_down(){
        if(this == NULLS) return ;
        if(rev){
            l->reverse();
            r->reverse();
            rev = 0;
        }
        if(flag) {
            l->add(flag);
            r->add(flag);
            flag = 0;
        }
    }
    void update()
    {
        mm = max(r->maxs - l->mins, val - l->mins); // 从深度大的到深度小的
        mm = max(mm,r->maxs - val);
        mm = max(mm,l->mm);
        mm = max(mm,r->mm);
        mm = max(0,mm);

        rmm = max(l->maxs - r->mins, val - r->mins);
        rmm = max(rmm, l->maxs - val);
        rmm = max(rmm,l->rmm);
        rmm = max(rmm,r->rmm);
        rmm = max(0,rmm);

        maxs = max(l->maxs,r->maxs);
        maxs = max(maxs,val);

        mins = min(l->mins,r->mins);
        mins = min(val,mins);
    }
    void reverse()
    {
        if(this == NULLS) return;
        rev = !rev;
        swap(l,r);
        swap(rmm,mm);
    }
    void add(int adder)
    {
        if(this == NULLS ) return;
        val += adder;
        maxs += adder;
        mins += adder;
        flag += adder;
    }
};
node EMP;
node * node::NULLS = (&EMP);
node * NULLS = node::NULLS;
node memstack[MAXN];
int memp;
node * NEWNODE(int v)
{
    node * p = &memstack[++memp];
    p->mm = p->rmm = 0;
    p->maxs = p->mins = p->val = v;
    p->path = NULLS;
    p->l = p->r = p->fa =  NULLS;
    p->rev = false;
    p->flag = 0;
    return p;
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
vector<int> maps[MAXN];
bool vis[MAXN];
int fa[MAXN];
node * tonode[MAXN];
int data[MAXN];
void dfs(int now)
{
    vis[now] = 1;
    for (int i = 0; i < sz(maps[now]); i++) {
        int &to = maps[now][i];
        if(!vis[to])
        {
            dfs(to);
            fa[to] = now;
        }
    }
}

void clear()
{
    for (int i = 0; i <= N; i++) {
        maps[i].clear();
    }
    clr(vis);
    clr(fa);
    clr(tonode);
    clr(data);
    memp = 0;
}
void build()
{
    dfs(1);
    for (int i = 1; i <= N; i++) {
        tonode[i] = NEWNODE(data[i]);
    }
    for (int i = 1; i <= N; i++) {
        if(fa[i] != 0)
        tonode[i]->path = tonode[fa[i]];
    }
}
void make_root(int x)
{
    node * p = tonode[x];
    access(p);
    p->reverse();
}
int query(int beg,int end,int adder)
{
    node * y = tonode[end];
    make_root(beg);
    access(y);
    int ans = y->mm;
    y->add(adder);
    return ans;
}
int main(int argc, char *argv[])
{
    ios::sync_with_stdio(0);
    NULLS->val = 0;
    NULLS->maxs = -INF;
    NULLS->mins = INF;
    NULLS->mm = NULLS->rmm = 0;
    // cin >> T;
    scanf("%d",&T);
    for (int tt = 1; tt <= T; ++tt) {
        // cin >> N;
        scanf("%d",&N);
        for (int i = 1; i <= N; i++) {
            // cin >> data[i];
            scanf("%d",data + i);
        }
        for (int i = 1; i < N; i++) {
            // cin >> a >> b;
            scanf("%d%d",&a,&b);
            maps[a].pb(b);
            maps[b].pb(a);
        }
        build();
        // cin >> Q;
        scanf("%d",&Q);
        for (int i = 1; i <= Q; i++) {
            // cin >> a >> b >> c;
            scanf("%d%d%d",&a,&b,&c);
            cout << query(a,b,c) << '\n';
        }
        clear();
    }
    return 0;
}