#include <bits/stdc++.h>

using namespace std;
//using namespace Dinic;

int deg[N];

void redirect_edges()   {
    for(auto it : index)    {
        int u = it.first.first;
        int v = it.first.second;

        if (index.count(ii(v,u)))   {
            Dinic::addEdge(u,v,1);
            continue;
        }        
        deg[u]++;
        deg[v]--;
    }
    Dinic::S = N - 2;
    Dinic::T = N - 1;

    for(int i = 0 ; i < vertices ; ++i) {
        if (deg[i] < 0) Dinic::addEdge(N - 2,i,-deg[i]);
        if (deg[i] > 0) Dinic::addEdge(i,N - 1, deg[i]);
    }
    Dinic::MaxFlow();

    for(int i = 0 ; i < sz(Dinic::E) ; ++i) {
        if (Dinic::E[i].v     == Dinic::T)  continue;
        if (Dinic::E[i ^ 1].v == Dinic::S)  continue;

        int v = Dinic::E[i].v;  i ^= 1;
        int u = Dinic::E[i].v;  i ^= 1;

        index.erase(ii(v,u));

        deg[u]++;
        deg[v]--;
    }
}