vector<pii> edges[MAXN];

//接受的图为vector<pii>,同时需要修改feach
int sccn[MAXN];
int dfn[MAXN];
int low[MAXN];
int dfc,cscc;
stack<int> S;

void tarjan(int now)
{
	 low[now]=dfn[now] = ++dfc;//增加时间戳
	 S.push(now);//在堆栈中放入点
	 feach(edges[now],i)
	 {
		  int to = i->x;
		  if(!dfn[to])
			   tarjan(to),low[now] = min(low[now],low[to]);
		  else if(!sccn[to])
			   low[now] = min(low[now],dfn[to]);
	 }
	 if(low[now] == dfn[now])
	 {
		  cscc++;
		  while(1)
		  {
			   int x = S.top();
			   S.pop();
			   sccn[x] = cscc;
			   if(x == now)
					break;
		  }
	 }
}
