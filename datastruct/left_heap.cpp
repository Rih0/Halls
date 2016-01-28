//all the functions return a number(except for top() ) representing a fake 'pointer'
const int MAXnode = MAXN;
struct leftist
{
	 int tot,v[MAXnode],l[MAXnode],r[MAXnode],d[MAXnode];
	 int merge(int x,int y) {
		  if(!x)
			   return y;
		  if(!y)
			   return x;
		  if(v[x]<v[y]) //make sure that x is the root with more nodes
			   swap(x,y);
		  r[x] = merge(r[x],y);
		  if(d[l[x]] < d[r[x]])
			   swap(l[x],r[x]);
		  d[x] = d[r[x]] + 1;
		  return x;
	 }
	 int init(int x) {
		  tot++;
		  v[tot] = x;
		  l[tot] = r[tot] = d[tot] = 0;
		  return tot;
	 }
	 int insert(int x,int y) {
		  return merge(x,init(y));
	 }
	 int top(int x) {
		  return v[x];
	 }
	 int pop(int x) {
		  return merge(l[x],r[x]);
	 }
};
leftist ltree;