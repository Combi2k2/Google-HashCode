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

typedef pair<int,int>   ii;

vector<int> adj_list[N];

map<ii,int> index;

int cost[N * 5];
int point[N * 5];

int vertices;
int edges;
int Time;
int Count;
int Start;