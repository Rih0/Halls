// 这段代码取自poj某题目，二分答案后，验证是否存在负权环
// 边权的计算是当前价格减去货物的价格，再乘上个什么。
bool negloop(int beg,int wealth)
{
    qtail = 1;
    q[++qhead] = beg;
    dist[beg] = wealth;
    while(qhead >= qtail)
    {
        int now = q[qtail++];
        inq[now] = 0;
        for(node * p =head[now];p;p=p->next)
        {
            double len = (dist[now] - p->c) * p->r;
            if(len > dist[p->to])
            {
                dist[p->to] = len;
                if(!inq[p->to])
                {
                    q[++qhead] = p->to,inq[p->to] = 1,incnt[p->to]++;
                    if(incnt[p->to] > N/4)
                    return 1;
                }
            }
        }
    }
    return 0;
}