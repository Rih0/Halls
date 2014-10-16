// zkw
// sample : Andrew Stankevich's Contest (3) Beloved sons
// codeforces http://codeforces.com/gym/100198
// 5.10.2014 7day happy ACS-3

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
#define feach(arr,e) for (vector<edge_t>::itr e=(arr).begin();e!=(arr).end();++e)
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

const int MAXN = 411 * 3;

int N;
int S,T;
int love[MAXN];
bool vis[MAXN];
struct edge_t{
    int to;
    int rest,cost;
    int back;
    edge_t(){};
    edge_t(int to,int rest,int cost):to(to),rest(rest),cost(cost){};
};
vector<edge_t> maps[MAXN];
int add_edge(int a,int b,int rest,int cost)
{
    maps[a].pb(edge_t(b,rest,cost));
    maps[b].pb(edge_t(a,0,-cost));
    maps[a][maps[a].size() - 1].back = maps[b].size() - 1;
    maps[b][maps[b].size() - 1].back = maps[a].size() - 1;
    return maps[a].size() - 1;
}
int a,b,c;

void build()
{
    ft(i,1,N)
    {
        add_edge(S,i,1,-love[i]);
    }
    ft(i,1,N)
    {
        add_edge(N+i,T,1,0);
    }
}

int cost,pi1;
int aug(int num,int totflow)
{
    if (num == T)
    {
        return cost += pi1 * totflow, totflow;
    }
    vis[num] = 1;
    int rest = totflow;
    feach(maps[num],p){
        if(p->rest && !p->cost && !vis[p->to]){
            int temp = aug(p->to,min(p->rest,rest));
            p->rest -= temp, maps[p->to][p->back].rest += temp, rest -= temp;
            if(!rest) break;
        }
    }
    return totflow - rest;
}
bool modify()
{
    int d = INF;
    for (int i = S; i <= T; ++i)
    {
        if(vis[i]){
            feach(maps[i],p){
                if(p->rest && !vis[p->to] && p->cost < d)
                d = p->cost;
            }
        }
    }
    if(d == INF)
    return 0;
    for (int i = S; i <= T; ++i)
    {
        if(vis[i]){
            feach(maps[i],p){
                p->cost -= d;
                maps[p->to][p->back].cost +=d;
            }
        }
    }
    pi1 += d;
    return 1;
}
void zkw()
{
    do
    do
    clr(vis);
    while(aug(S,INF));
    while(modify());
}

// zkw ends here
vector<pii> keyedge;
int ans[MAXN];
void show()
{
    for (vector<pii>::itr i = keyedge.begin(); i != keyedge.end(); ++i)
    {
        if(maps[i->x][i->y].rest == 0)
        {
            ans[i->x] = maps[i->x][i->y].to - N;
        }
    }
    ft(i,1,N)
        printf("%d ",ans[i]);
}
int main(int argc, char *argv[])
{
    scanf("%d",&N);
    S = 0;
    T = N * 2 + 1;
    ft(i,1,N)
    {
        scanf("%d",love + i);
    }
    ft(i,1,N)
    {
        int cnt;
        scanf("%d",&cnt);
        ft(j,1,cnt)
        {
            scanf("%d",&a);
            int pos = add_edge(i,N + a,1,0);
            keyedge.pb(pii(i,pos));
        }
    }
    build();
    zkw();
    show();
    return 0;
}