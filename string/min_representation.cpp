
int MinRepresstation(string S)
{
	 int i = 0, j = 1, k = 0;
	 int len = S.length();
	 S += S;
	 while(i < len && j < len)
	 {
		  k = 0;
		  while(k < len && S[i + k] == S[j + k])
			   k++;
		  if(k >= len)
			   break;
		  if(S[i + k] > S[j + k])
			   i = max(i + k + 1, j + 1);
		  else
			   j = max(i + 1, j + k + 1);
	 }
	 return min(i ,j);          // 返回的是起点
}