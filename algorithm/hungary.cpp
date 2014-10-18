int match[];//匹配图
bool dfs(int now)
{
	for(int )//遍历当前点的临接点
	{
		int &to=;//某个临接点
		if(!vis[to])
		{
			vis[to]=1;
			if(!match[to]||dfs(match[to]))//可以增广或者可以取反增广
			{
				match[to]=now;
				return 1;
			}
		}
	}
	return 0;
}
int hungary()
{
	int ans=0;
	for(int i=1;i<=N;i++)
	{
		memset(vis,0,sizeof(vis));
		ans+=dfs(i);
	}
	return ans;
}
