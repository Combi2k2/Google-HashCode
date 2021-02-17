#include <bits/stdc++.h>
#include "ReadInput.hpp"

using namespace std;

int Sum_Pool[1005];
int Max_Pool[1005];

int Cap_in_Row[1005][1005];

int Pos_x[1005];
int Pos_y[1005];
int in_Pool[1005];

int main()  {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    freopen("large_input.in","r",stdin);
    freopen("output.txt","w",stdout);

    readInput();

    priority_queue<ii,vector<ii>,greater<ii> >  Pool_queue;

    for(int i = 0 ; i < pools ; ++i)
        Pool_queue.push(ii(0,i));

    for(ii  SV : servers)   {
        int id_pool = Pool_queue.top().second;
        int id_server  = SV.second % sz(servers);

        Pool_queue.pop();

        in_Pool[id_server] = id_pool;

        Pos_x[id_server] = -1;
        Pos_y[id_server] = -1;

        vector<int> vec(row);
        
        iota(all(vec),0);
        sort(all(vec),[&](int x,int y)  {
            return  Cap_in_Row[id_pool][x] < Cap_in_Row[id_pool][y];
        });
        bool ok = false;

        for(int i : vec)    {
            for(ii  interval : seg[i])  {
                int l = interval.first;
                int r = interval.second;

                if (r - l + 1 >= SV.first)  {   //this server has size fitting in the space
                    Pos_x[id_server] = i;
                    Pos_y[id_server] = l;

                    seg[i].erase(find(all(seg[i]),ii(l,r)));    l += SV.first;

                    if (l <= r) seg[i].pb(ii(l,r));

                    ok = true;
                    break;
                }
            }
            if (ok) break;
        }
        int cap = SV.second / sz(servers);

        if(!ok) continue;
        else    {
            Cap_in_Row[id_pool][Pos_x[id_server]] += cap;

            if (Max_Pool[id_pool] < Cap_in_Row[id_pool][Pos_x[id_server]])
                Max_Pool[id_pool] = Cap_in_Row[id_pool][Pos_x[id_server]];
            
            Sum_Pool[id_pool] += cap;
            
            Pool_queue.push(ii(Sum_Pool[id_pool] - Max_Pool[id_pool],id_pool));
        }
    }
    for(int i = 0 ; i < sz(servers) ; ++i)  {
        if (Pos_x[i] < 0)   {
            cout << "x\n";
            continue;
        }
        cout << Pos_x[i] << " ";
        cout << Pos_y[i] << " ";
        cout << in_Pool[i] << "\n";
    }
    cerr << Pool_queue.top().first << "\n";
}
