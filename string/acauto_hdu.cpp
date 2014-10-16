// hdu2896
// basic AC automaton
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
#define feach(arr,i) for(__typeof(arr.begin()) i=(arr.begin());i!=(arr.end());++i)
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

const int MAXN_C = 128;
const int Cbase = 0;
struct node
{
     int id;
	 node * next[MAXN_C],*fail;
	 node(int id = 0):id(id) {
			   fail = NULL;
			   clr(next);
		  }
} * head = new node();

void ac_insert(char * s,int id)
{
	 node * p = head;
	 int len = strlen(s + 1);
	 for(int i = 1; i <= len ; i++)
	 {
		  int idx = s[i] - Cbase;
		  if(!p->next[idx])
			   p->next[idx] = new node();
		  p = p->next[idx];
	 }
	 p -> id = id;
}
queue<node *> Q;
void ac_fail()
{
	 head -> fail = NULL;
	 Q.push(head);
	 while(!Q.empty())
	 {
		  node * now = Q.front();
		  Q.pop();
		  ft(i,0,MAXN_C-1)
		  {
			   if(!now->next[i])
			   {
					now->next[i] = (now->fail == NULL) ? head : now->fail->next[i];
					continue;
					//直接建立为有限状态机
			   }
			   node * p = now ->fail;
			   while(p)
			   {
					if(p->next[i])
					{
						 now->next[i]->fail = p->next[i];
						 break;
					}
					p = p->fail;
			   }
			   if ( p == NULL)
					now->next[i]->fail = head;
			   Q.push(now->next[i]);
		  }
	 }
}
veci ans;
void ac_find(char * s,int webid)
{
     int len = strlen(s + 1);
     node * p = head;
     ft(i,1,len)
     {
          int idx = s[i] - Cbase;
          p = p->next[idx];

		  //查询所有已匹配的部分
          node * temp = p;
          while (temp != head)
          {
               if(temp->id)
                    ans.pb(temp->id);
               temp = temp->fail;
          }
     }
}

char str[10000];
char mstr[1000000];
int N,M;
int main()
{
     int cnt = 0;
     sf("%d",&N);
     ft(i,1,N)
     {
          sf("%s",str+1);
          ac_insert(str,i);     // 读入串并插入
     }
     ac_fail();
     sf("%d",&M);
     ft(i,1,M)
     {
          sf("%s",mstr+1);
          ac_find(mstr,i);
          srt(ans);
          if(sz(ans)!=0)
          {
               pf("web %d:",i);
               feach(ans,i)
                    pf(" %d",*i);
               puts("");
               cnt ++ ;
          }
          ans.clear();
     }
     pf("total: %d\n",cnt);
     //head = new node();
	 return 0;
}
