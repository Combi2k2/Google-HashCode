#include <bits/stdc++.h>
#include "CrucialData.hpp"
#include "greedy.hpp"

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
    freopen("answer_with_greedy.txt","w",stdout);

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

    vector<int> move[8];

    Main_of_Greedy(move);

    cerr << Count << "\n";

    for(int i = 0 ; i < Count ; ++i)    {
        cout << move[i].size() << "\n";
        for(int x : move[i])
            cout << x << "\n";
    }
}
