#include<iostream>
#include <cstdio>
#include <cstring>
#include<iostream>
#include<algorithm>
using namespace std;
const int MAXN=10000000;
char S[MAXN];
char T[MAXN];
int Slen,Tlen;
int next[MAXN];
int ex[MAXN];
void Getnext(char * s,int len)
{
	 next[1]=len;
	 for(int i=1;i<=len;i++)
	 {
		  if(s[i+1]!=s[i])
		  {
			   next[2] = i-1;
			   break;
		  }
	 }
	 ////////////
	 int j, k = 2, p, L;
	 for(int i = 3; i <= len; i++) 
	 {
		  p = k + next[k] - 1; 
		  L = next[i - k];
		  if (i + L <= p) 
			   next[i] = L; 
		  else 
		  {
			   j = p - i + 1;
			   if (j < 1) j = 1;
			   while (i + j < len && s[i + j] == s[j]) 
					j++;
			   next[i] = j; 	k = i; 
		  }
	 }
}

void Getex()
{
	 int minlen=min(Slen,Tlen);
	 ex[1]=minlen;
	 for(int i=1;i<=minlen;i++)
	 {
		  if(S[i]!=T[i])
		  {
			   ex[1]=i;
			   break;
		  }
	 }
	 int j,k=1,p,l;
	 for(int i=2;i<=Slen;i++)
	 {
		  p=k+ex[k]-1;
		  l=next[i-k];
		  if(i+l<=p)
			   ex[i]=l;
		  else
		  {
			   j=p-i+1;
			   if(j<1) 
					j=1;
			   while(i+j<=Slen&&j<Tlen&&S[i+j]==T[j])
					j++;
			   ex[i]=j;
			   k=i;
		  }
	 }
}
int main()
{
	 gets(&S[1]);
	 gets(&T[1]);
	 Slen=strlen(&S[1]);
	 Tlen=strlen(&T[1]);
	 Getnext(T,Tlen);
	 Getex();
	 for(int i=1;i<=Slen;i++)
		  cout<<ex[i]<<" ";
	 return 0;
}
