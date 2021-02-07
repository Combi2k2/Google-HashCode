#include<bits/stdc++.h>

using namespace std;

#define ll  long long
#define ld  double

#define sz(x)   (int)x.size()
#define all(x)  x.begin(),x.end()

#define pb  emplace_back
#define X   first
#define Y   second

const int   N   = 1e6 + 5;

vector<int> adj_list[N];

struct Edge {
    int v;
    int cost;
    int point;
    Edge(int _v = 0,int _c = 0,int _p = 0) : v(_v), cost(_c), point(_p) {}
}   E[N * 5];

int tot = 0;

void addEdge(int u,int v,int time,int length)   {
    adj_list[u].pb(tot);
    E[tot++] = Edge(v,time,length);
}
int vertices;
int edges;
int Time;
int Count;
int Start;