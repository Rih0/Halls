const int bitmax = MAXN-1;
template<class T>
struct bitarrtype
{
	 T bitarr[bitmax+1];
	 void add(int beg,T delta){
		  for (int i = beg ; i <= bitmax; i += lowbit(i))
			   bitarr[i] += delta;
	 }
	 T query(int num){
		  T ans = 0;
		  for (int i = num ; i; i -= lowbit(i))
			   ans+=bitarr[i];
		  return ans;
	 }
	 int findk(int k) {
		  int ret = 0;
		  for (int p = 1<<(int(log2(bitmax))); p; p >>= 1)
			   if (ret+p < bitmax && bitarr[ret+p] < k)
					k -= bitarr[ret+=p];
		  return ret+1;
	 }
};
//当将bitarr作为排名数组时，可以求一个数的排位（小于和等于它的数）和第k大的数的位置，支持插入和删除数