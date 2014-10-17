

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

struct node
{
	 LL sumlen,cover;
	 LL flag;
};
node tree[MAXN*4+100];

void change(int p,int tbeg,int tend,int beg,int end,int flag)
{
	 if(tbeg >= beg && tend <= end) //简化写法，因为不会查询到下面的点,仅对包含线段进行更新，其他值通过递推关系得到
     tree[p].cover += flag;
	 else
	 {
		  int mid=(tbeg+tend)>>1;
		  if(beg<mid)
			   change(p<<1,tbeg,mid,beg,end,flag);
		  if(mid<end)
			   change((p<<1)+1,mid,tend,beg,end,flag);
	 }
	 if(tree[p].cover>0)//本线段被覆盖了
		  tree[p].sumlen=tend-tbeg;
	 else
	 {
		  if(tbeg+1==tend)
			   tree[p].sumlen=0;
		  else
			   tree[p].sumlen=tree[p<<1].sumlen+tree[(p<<1)+1].sumlen;
	 }
}

int N;
struct edge
{
	 int x,y1,y2,flag;
};
edge data[MAXN*4*2];
int datap;
inline void addE(int x,int y1,int y2,int flag)
{
	 datap++;
	 data[datap].x = x;
	 data[datap].y1 = y1;
	 data[datap].y2 = y2;
	 data[datap].flag = flag;
}
void addRec(int x,int y,int xx,int yy)
{
	 if(x == xx || y == yy)
		  return ;
	 addE(x,y,yy,1);
	 addE(xx,y,yy,-1);
}
void getRec(pii outd,pii outu,pii ind,pii inu)
{
	 addRec(outd.x,outd.y,ind.x,outu.y);
	 addRec(ind.x,inu.y,inu.x,outu.y);
	 addRec(ind.x,outd.y,inu.x,ind.y);
	 addRec(inu.x,outd.y,outu.x,outu.y);
}
int a,b,c,d;
bool cmp(const edge a,const edge b)
{
	 if(a.x == b.x)
		  return a.flag > b.flag;
	 return a.x < b.x;
}
void solve()
{
	 sort(&data[1],&data[datap+1],cmp);
	 LL lastx = data[1].x;
	 LL ans = 0;
	 ft(i,1,datap)
	 {
		  ans += tree[1].sumlen*((LL)data[i].x-lastx);
		  change(1,1,Mseg,data[i].y1,data[i].y2-1+1,data[i].flag);
          //切记，此处不用在线段树线段末端点+1,因为联系其实际含义，其中间的长度，本来就是这个数
		  lastx = data[i].x;
	 }
	 cout << ans << "\n";
	 clr(tree);
	 datap = 0;
}
int main(int argc, char *argv[])
{
	 while(~sf("%d",&N))
	 {
		  if(!N)
			   break;
		  ft(i,1,N)
		  {
			   sf("%d%d%d%d",&a,&b,&c,&d);
			   a++,b++,c++,d++;//防止0点
			   pii outd(a,b),outu(c,d);
			   sf("%d%d%d%d",&a,&b,&c,&d);
			   a++,b++,c++,d++;
			   pii ind(a,b),inu(c,d);
			   getRec(outd,outu,ind,inu);
		  }
		  solve();
	 }
	 return 0;
}