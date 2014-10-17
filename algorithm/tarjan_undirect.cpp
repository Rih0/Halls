int vis[MAXN];
int dfn[MAXN],low[MAXN];
int dfc;
bool iscut[MAXN];
//bool brg[MAXN][MAXN];
int maxs=0;

vector<pii> edges[MAXN];

void cut_brg(int cur,int fa) //适用于没有重边的图
{
    vis[cur] = 1;
    dfn[cur] = low[cur] = ++dfc;
    int child = 0;
    int cuts = 0;
    feach(edges[cur],p)
    {
        int to = p->x;
        if(to != fa && vis[to]) //返祖边
        low[cur] = min(low[cur],dfn[to]);
        if(!vis[to])
        {
            cut_brg(to,cur);
            child++;
            low[cur] = min(low[cur],low[to]);
            if((fa == -1 && child > 1)||(fa != -1 && low[to] >= dfn[cur]))
            iscut[cur] = 1, cuts ++;
            if(low[to] > dfn[cur])  //brig judge
            brg[to][cur] = brg[cur][to] = 1;
        }
    }
    if(iscut[cur])
    maxs = max(maxs,cuts);
    vis[cur] = 2;
}

// 适用于有重边的图
vector<pr<pii,int> > brigs;
void cut_brg(int cur,node * fa) //适用于存在重边的图
{
	 vis[cur] = 1;
	 dfn[cur] = low[cur] = ++dfc;
	 for(node * p =head[cur];p;p=p->next)
	 {
		  int to = p->num;
		  if(fa!= NULL &&p != fa->back && vis[to]) //返祖边
			   low[cur] = min(low[cur],dfn[to]);
		  if(!vis[to])
		  {
			   cut_brg(to,p);
			   low[cur] = min(low[cur],low[to]);
			   if(low[to] > dfn[cur])
					brigs.pb(pr<pii,int>(pii(cur,to),p->val));
		  }
	 }
}
