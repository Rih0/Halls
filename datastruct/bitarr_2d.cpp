
const int xbitmax = MAXN -1;
const int ybitmax = MAXN -1;
template<class T>
struct bitmattype
{
	 T mat[MAXN][MAXN];
	 // (xx,yy)+(x-1,y-1)-(xx,y-1)-(x-1,yy)
	 void add(int x,int y,T delta){
		  for(int i=x ;i<=xbitmax;i += lowbit(i))
			   for (int j=y ;j <= ybitmax; j += lowbit(j))
					mat[i][j] += delta;
	 }
	 T query(int a,int b){
		  T ans = 0;
		  for (int i=a ; i ; i -= lowbit(i))
			   for (int j=b ; j; j -= lowbit(j))
					ans += mat[i][j];
		  return ans;
	 }
};
