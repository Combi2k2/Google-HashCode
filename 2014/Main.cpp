#include <bits/stdc++.h>
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

        int time;   cin >> time;
        int length; cin >> length;

        if (dir == 1)   addEdge(u,v,time,length);
        if (dir == 2)   addEdge(u,v,time,length), addEdge(v,u,time,length);
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
