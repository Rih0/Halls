void kmp(char * s,char * t,int * next)
{
	 int slen = strlen(&s[1]);
	 int tlen = strlen(&t[1]);
	 int j=0;
	 int cnt = 0;
	 ft(i,1,slen)
	 {
		  while(j != 0 && s[i]!=t[j+1]) j = next[j];
		  if(s[i] == t[j+1]) j++;
		  if(j == tlen) j=next[j],cnt++;
	 }
}
void getnext(char * s,int * next)
{
	 int slen=strlen(&s[1]);
	 next[1]=0;
	 int j=0;
	 ft(i,2,slen)
	 {
		  while(j != 0 && s[i] != s[j+1]) j=next[j];
		  if(s[i] == s[j+1]) j++;
		  next[i] = j;
	 }
}
//所以可以推出一个重要的性质len-next[i]为此字符串的最小循环节(i为字符串的结尾)，另外如果
//len%(len-next[i])==0,此字符串的最小周期就为len/(len-next[i]);