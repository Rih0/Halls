template<class T>
class mtype
{
public:
     T mat[110][110];
     static int MAXN;
     mtype(){
            clr(mat);
     }
     void show(int M) {
            for (int i = 1; i <= M; ++i,puts(""))
                  for (int j = 1; j <= M; ++j)
                         pf("%I64d ",mat[i][j]);
     }
     mtype operator * (const mtype& b) {
            mtype temp;
            for(int i=1;i<=MAXN;i++)
                  for(int j=1;j<=MAXN;j++)
                         for(int k=1;k<=MAXN;k++)
                         {
                              temp.mat[i][j] += mat[i][k] * b.mat[k][j];
                              temp.mat[i][j] %= MODS;
                         }
            return temp;
     }
     mtype getpow(int k) {

            mtype ans;
            mtype bitp = *this;
            ft(i,1,MAXN)
                  ans.mat[i][i] = 1;
            while(k)
            {
                  if(k & 1)
                         ans = ans * bitp;
                  bitp = bitp * bitp;
                  k = k >> 1;
            }
            return ans;
     }
};
template<>
int mtype<LL>::MAXN = 1;