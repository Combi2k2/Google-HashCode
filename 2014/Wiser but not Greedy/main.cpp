#include <bits/stdc++.h>
#include "CrucialData.hpp"
#include "Flow.hpp"
#include "Dijkstra.hpp"

#include "Orienting_undirected_edges.hpp"
#include "Edge_Complementation.hpp"

using namespace std;

#define ll  long long
#define ld  double

#define sz(x)   (int)x.size()
#define all(x)  x.begin(),x.end()

#define pb  emplace_back
#define X   first
#define Y   second

int main()  {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    freopen("input.txt","r",stdin);
    freopen("answer_but_wiser.txt","w",stdout);

    cin >> vertices;
    cin >> edges;

    cin >> Time;
    cin >> Count;

    cin >> Start;

    for(int i = 0 ; i < vertices ; ++i) {
        ld  x;  cin >> x;
        ld  y;  cin >> y;
    }
    for(int i = 0 ; i < edges ; ++i)    {
        int u;  cin >> u;
        int v;  cin >> v;

        int dir;    cin >> dir;

        cin >> cost[i];
        cin >> point[i];

        if (dir == 1)   adj_list[u].pb(v),  index[ii(u,v)] = i;
        if (dir == 2)   {
            adj_list[u].pb(v);  index[ii(u,v)] = i;
            adj_list[v].pb(u);  index[ii(v,u)] = i;
        }
    }
    /*******************
     * THE ABOVE PART IS TO READ INPUT
     */
    redirect_edges();
}
