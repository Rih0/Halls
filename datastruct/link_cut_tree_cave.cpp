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
const int INF = 0x7f7f7f7f;
const double dboo=1e+20;
const double eps=1e-8;
const double pi=acos(-1.0);
const int MOD=1000000007;
const int MAXN = 11000;
int N,M;
struct node
{
    int num;
    node * l, *r;
    node * fa,* path;
    bool rev;
    static node * NULLS;
    void reverse(){
        if(this == NULLS){
            return ;
        }
        rev = !rev;
        swap(l,r);
    }
    void push_down(){
        if(rev){
            rev = 0;
            l->reverse();
            r->reverse();
        }
    }
    void update(){}
};
node EMP;
node * node::NULLS = (&EMP);
node * NULLS = node::NULLS;
node data[MAXN];
int datap;
node * tonode[MAXN];
int fa[MAXN];
node * NEWNODE(int i)
{
    node * p = &data[++datap];
    p->num = i;
    p->l = p->r = p->fa = p->path = NULLS;
    p->rev = 0;
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
}
#define SAMELINE(p,chd) (p->fa->fa->chd == p->fa && p->fa->chd == p)
void splay(node * p)
{
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
        y = x;                              // 迭代
        x = x->path;                        // 迭代
    }
    splay(p);
}
int find_root(node * p)
{
    while(p->l != NULLS){
        p = p->l;
    }
    return p->num;
}
void link(node * a,node * b)
{
    access(a);                  // 树上最深点使之成为最小点
    a->reverse();               // 翻转使得它成为根
    a->path = b;                // 同上
    access(a);                  // 更新信息
}
void cut(node * a,node * b)
{
    access(a);
    a->reverse();               // a成为树根
    access(b);                  // b加入关键路径
    b->l->path = NULLS;         // 切割
    b->l->fa = NULLS;           // 切割
    b->l = NULLS;               // 切割
}
void query(node * a,node * b)
{
    access(a);
    int rt1 = find_root(a);
    access(b);
    int rt2 = find_root(b);
    if (rt1 == rt2) {
        printf("Yes\n");
    } else {
        printf("No\n");
    }
}
char str[123];
int a,b;
int main(int argc, char *argv[])
{
    scanf("%d%d",&N,&M);
    for (int i = 1; i <= N; ++i)
    {
        tonode[i] = NEWNODE(i);
    }
    for (int i = 1; i <= M; ++i)
    {
        scanf("%s%d%d",str + 1, &a, &b);
        if (str[1] == 'C') {
            link(tonode[a],tonode[b]);
        } else if (str[1] == 'D') {
            cut(tonode[a],tonode[b]);
        } else {
            query(tonode[a],tonode[b]);
        }
    }
    return 0;
}