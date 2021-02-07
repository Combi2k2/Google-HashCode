/*************************************************************************
 * This is to use greedy method, finding the most optimal direction in current moment
 * Then update traversed edge until the time runs out
 */
#include <bits/stdc++.h>
#include "CrucialData.hpp"

using namespace std;

#define ll  long long
#define ld  double

#define sz(x)   (int)x.size()
#define all(x)  x.begin(),x.end()

#define pb  emplace_back
#define X   first
#define Y   second

const int   DEPTH = 10;

int min_vehicle(int *temps) {
    int earliest_val = Time + 1;
    int earliest_pos = 0;

    for(int i = 0 ; i < Count ; ++i)
        if (earliest_val > temps[i])    {
            earliest_val = temps[i];
            earliest_pos = i;
        }
    return  earliest_pos;
}
typedef pair<int,int>   ii;

bool visit[N * 5];

ii  explore(int depth,int u,int cost) {
    if (depth == 0) return  ii(u,0);

    int best_val = -1;
    int best_dir = -1;

    for(int i : adj_list[u])    {
        int current_score = 0;

        bool visited = visit[i];
        if (!visited)   current_score = E[i].point;

        cost += E[i].cost;  visit[i] = true;    current_score += explore(depth - 1,E[i].v,cost).second;
        cost -= E[i].cost;  visit[i] = visited;

        if (best_val < current_score)   {
            best_val = current_score;
            best_dir = i;
        }
    }
    return  ii(best_dir,best_val);
}
void Main_of_Greedy(vector<int> *path)  {
    int pos[8];
    int leng[8];
    int answer = 0;
    
    for(int i = 0 ; i < 8 ; ++i)
        pos[i] = Start,
        leng[i] = 0,
        path[i].pb(Start);
    
    int car;

    while (leng[car = min_vehicle(leng)] <= Time)   {
        ii  next_step = explore(DEPTH,pos[car],leng[car]);
        if (next_step.second == 0)
            break;
        
        int dir = next_step.first;
        //if(!dir)    {
        //    cerr << "Bug vl :)))\n";
        //    break;
        //}
        //cerr << "move from " << car << " to " << dir << "\n";

        path[car].pb(E[dir].v);
        leng[car] += E[dir].cost;

        pos[car] = E[dir].v;
        answer += (visit[dir] ? 0 : E[dir].point);
        visit[dir] = true;
    }
}