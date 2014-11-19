// poj 1330
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
#define feach(arr,i) for(vector<pii>::itr i=(arr.begin());i!=(arr.end());++i)
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

const int MAXN =11111;
int t;
int N;
vector<int> maps[MAXN];

const int SecMax=20;
struct Lcatype
{
    int Dep[MAXN*3];
    int Fir[MAXN*3];
    int DFS[MAXN*3];
    bool vis[MAXN];
    int Dp;
    int f[MAXN*3][21];//mul 3 for dfs sequence has 3*cnt of maxns
    int Sec[SecMax];

    void dfs(int num,int dep){

        vis[num]=1;
        Dep[++Dp]=dep;
        DFS[Dp]=num;
        Fir[num]=Dp;

        for(vector<int>::itr i = maps[num].begin();i!=maps[num].end();++i)
        {
            int &to = *i;
            if(!vis[to])
            {
                dfs(to,dep+1);
                Dep[++Dp]=dep;
                DFS[Dp]=num;
            }
        }
    }

    int Closed(int now){
        for(int i=0;i<=SecMax;i++)
        {
            if(Sec[i+1]>=now)
            return i;
        }
    }
    void init(int treehead){

        clr(vis);
        Dp = 0;
        dfs(treehead,0);//dfs
        for(int i=1;i<=Dp;i++)
        f[i][0]=i;
        Sec[0]=1;
        for(int i=1;i<SecMax;i++)
        Sec[i]=(1<<i);
        int K=Closed(Dp);
        for(int i=1;i<=K;i++)
        for(int j=1;j<=Dp-Sec[i]+1;j++)
        {
            if(Dep[f[j][i-1]]<Dep[f[j+Sec[i-1]][i-1]])
            f[j][i]=f[j][i-1];
            else
            f[j][i]=f[j+Sec[i-1]][i-1];
        }
    }
    int lca(int a,int b){
        if(Fir[a]>Fir[b])
        swap(a,b);
        int i=Closed(Fir[b]-Fir[a]+1);
        if(Dep[f[Fir[a]][i]]<Dep[f[Fir[b]-Sec[i]+1][i]])
        return DFS[f[Fir[a]][i]];
        else
        return DFS[f[Fir[b]-Sec[i]+1][i]];
    }
};
Lcatype lca;
int a,b;
bool showed[MAXN];
int main(int argc, char *argv[])
{
    sf("%d",&t);
    while(t--)
    {
        sf("%d",&N);
        ft(i,1,N-1)
            sf("%d%d",&a,&b),maps[a].pb(b),maps[b].pb(a),showed[b] = 1;
        ft(i,1,N)
            if(!showed[i])
            lca.init(i);
        sf("%d%d",&a,&b);
        cout << lca.lca(a,b) << "\n";
        clr(showed);
        ft(i,1,N)
            maps[i].clear();
    }
    return 0;
}