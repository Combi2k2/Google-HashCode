#include <bits/stdc++.h>

using namespace std;

#define ll  long long
#define ld  double

#define sz(x)   (int)x.size()
#define all(x)  x.begin(),x.end()

#define pb  emplace_back
#define X   first
#define Y   second

typedef pair<ll,int>    pli;

priority_queue<pli,vector<pli>,greater<pli> >   pq;

namespace Dijkstra  {
    vector<ll>  d;
    vector<int> path;
    
    void proc(int nVertices,int Src)    {
        d.assign( nVertices,1e18);
        d[Src] = 0;

        pq.push(pli(0,Src));

        while (pq.size())   {
            ll  du = pq.top().first;
            int u  = pq.top().second;   pq.pop();

            if (du != d[u]) continue;

            for(int v : adj_list[u])
                if (d[v] > du + cost[index(u,v)])   {
                    d[v] = du + cost[index(u,v)];
                    pq.push(pli(d[v],v));
                }         
        }
    }
    void trace(int nVertices,int Src,int Dst)   {
        proc(nVertices,Src);
        path.clear();

        if (d[Dst] == 1e18) return;
    }
};