#include <cstdio>
#include <cstring>
#include <set>
#include <cstdlib>
#include <iostream>

using namespace std;
int T,N;
int a,b;
struct point
{
    int x,y;
    point(int a,int b):x(a),y(b){}
    bool operator < (const point & b) const
    {
        return x < b.x || (x == b.x && y < b.y);
    }
};
multiset<point> data;
typedef multiset<point>::iterator msp;
void insert(int x,int y)
{
    point now = point(a,b);
    //data.insert(now);
    msp lp = data.lower_bound(now);
    if(lp == data.begin() || (--lp)->y > y){
        data.insert(now);
        msp rp = data.upper_bound(now);
        while(rp != data.end() && rp->y >= y) data.erase(rp++); // rp-y >= y 严格的凸包
    }
    printf("%d\n",data.size());
    // puts("");
}
int main(int argc, char *argv[])
{
    scanf("%d",&T);
    for (int tt = 1; tt <= T; ++tt) {
        if(tt > 1) puts("");
        scanf("%d",&N);
        printf("Case #%d:\n",tt);
        for (int i = 1; i <= N; i++) {
            scanf("%d%d",&a,&b);
            insert(a,b);
        }
        data.clear();
    }
    return 0;
}

