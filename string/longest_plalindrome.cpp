int rid[100000];
string mana(const char *s)
{
    string t, res;
    int L = strlen(s);
    // init
    t += '?';
    for(int i = 0; i < L; i++)
    t += '#', t += s[i];
    t += "#*";
    // getrid
    for(int i=1,j=0,k,End=(int)t.size();i<End;){
        while( t[i-j-1]==t[i+j+1] ) j++;
        rid[i] = j;
        for(k=1;k<=j&&(rid[i-k]!=rid[i]-k);k++)
        rid[i+k] = min( rid[i-k], rid[i]-k );
        i += k;
        j = max( 0,j-k );
    }
    // Max
    int m = 0, pos;
    for(int i = 1; i < (int)t.size(); i++){
        if( m < rid[i]*2+(t[i]!='#') )
        m = rid[i]*2+(t[i]!='#'), pos = i;
    }
    for(int i = pos-rid[pos]; i <= pos+rid[pos]; i++){
        if( t[i] != '#' ) res += t[i];
    }
    return res;
}

int calcit(const char * a)
{
    string fuck = mana(a);
    return fuck.length();
}