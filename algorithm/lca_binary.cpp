// mst and maxcost dynamic
// uva 11354
#include <iostream>
#include <cstdio>
#include <vector>
#include <map>
#include <cstring>
#include <algorithm>
using namespace std;

#define clr(x) memset((x),0,sizeof(x))
#define x first
#define y second
#define sz(x) int(x.size())
#define all(x) (x).begin(),(x).end()
typedef pair<int,int> pii;
typedef pair<int,pair<int,int> > piii;
const int MAXN = 51111;
const int INF = 0x3f3f3f3f;


int N,M,Q;
vector<pii> maps[MAXN];

vector<piii> edges;
vector<pii> newmap[MAXN];

int bcj[MAXN];
bool vis[MAXN];
int fa[MAXN];
int cost[MAXN];
int dep[MAXN];

int maxcost[MAXN][30];
int anc[MAXN][30];

void clear()
{
    clr(maxcost);
    clr(anc);
    clr(vis);
    clr(fa),clr(cost),clr(dep);
    edges.clear();
    for (int i = 0; i <= N; i++) {
        maps[i].clear();
        newmap[i].clear();
    }
}

void dfs(int v,int nth)
{
    vis[v] = 1;
    for (int i = 0; i < sz(newmap[v]); i++) {
        int to = newmap[v][i].x;
        if(!vis[to]) {
            fa[to] = v;
            cost[to] = newmap[v][i].y;
            dep[to] = nth + 1;
            dfs(to,nth + 1);
        }
    }
}

void init()
{
    for (int i = 1; i <= N; i++) {
        anc[i][0] = fa[i];
        maxcost[i][0] = cost[i];
        for (int j = 1; (1 << j) <= N; ++j) {
            anc[i][j] = -1;     // 首先把所有的都写成1不存在的都写成-1
        }
    }
    for (int j = 1; (1 << j) <= N; j++) {      // 遍历j
        for (int i = 1; i <= N; i++) {
            if(anc[i][j-1] != -1)              // 如果子问题已经计算了，或者说子问题存在
            {
                int anc1 = anc[i][j-1];        // i的祖先
                anc[i][j] = anc[anc1][j-1];    // i
                maxcost[i][j] = max(maxcost[i][j-1], maxcost[anc1][j-1]);
            }
        }
    }
}

int getfa(int i)
{
    if(bcj[i] == i)
    return i;
    return bcj[i] = getfa(bcj[i]);
}
void merge(int a,int b)
{
    int afa = getfa(a);
    int bfa = getfa(b);
    bcj[afa] = bfa;
}
bool same(int a,int b)
{
    return getfa(a) == getfa(b);
}
void mst()
{
    for (int i = 0; i <= N; i++) {
        bcj[i] = i;
    }
    sort(all(edges));
    for (int i = 0; i < sz(edges); i++) {
        int from = edges[i].y.x;
        int to = edges[i].y.y;
        int len = edges[i].x;
        if(!same(from,to)){
            // cout << from << " " << to << endl;
            merge(from,to);
            newmap[from].push_back(pii(to,len));
            newmap[to].push_back(pii(from,len));
        }
    }
}
void build()
{
    mst();

    clr(vis);
    fa[1] = 0;
    cost[1] = INF;
    dep[1] = 0;
    dfs(1,0);

    init();
}
int query(int a,int b)
{
    int log = 1;
    if(dep[a] < dep[b]) swap(a,b);
    while((1 << log) <= dep[a]) log++;

    int ans = -INF;

    for (int i = log; i >= 0; --i) {
        if(dep[a] - (1 << i) >= dep[b]){
            ans = max(ans,maxcost[a][i]);
            a = anc[a][i];
        }
    }
    // 将a收到深度与b相同的位置

    if(a == b) return ans;      // 直接收到了b点，说明lca为b

    // 如果没有收到lca上，那么此时，两个点的深度相同，一起收，直到到lca直接相接的下面
    for (int i = log; i >= 0; i--) {
        if(anc[a][i] != -1 && anc[a][i] != anc[b][i]){
            // anc[a][i] == anc[b][i]时，说明收到了lca之上
            ans = max(ans,maxcost[a][i]);
            a = anc[a][i];
            ans = max(ans,maxcost[b][i]);
            b = anc[b][i];
        }
    }

    ans = max(ans,cost[a]);
    ans = max(ans,cost[b]);

    return ans;
}

int a,b,c;
int main(int argc, char *argv[])
{
    int tt = 0;
    while(scanf("%d%d",&N,&M) != EOF)
    {
        if(tt) puts("");
        for (int i = 1; i <= M; i++) {
            scanf("%d%d%d",&a,&b,&c);
            maps[a].push_back(pii(b,c));
            maps[b].push_back(pii(a,c));
            edges.push_back(piii(c,pii(a,b)));
        }
        build();
        scanf("%d",&Q);
        for (int i = 1; i <= Q; i++) {
            scanf("%d%d",&a,&b);
            printf("%d\n",query(a,b));
        }
        clear();
        tt ++;
    }
    return 0;
}



