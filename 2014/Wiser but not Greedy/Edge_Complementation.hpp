#include <bits/stdc++.h>

using namespace std;

namespace DSU   {
    vector<int> p;
    vector<int> s;

    int init(int n) {
        p.resize(n);    iota(all(p),0);
        s.assign(n,0);  return  1;
    }
    int lead(int x) {   return  p[x] == x ? x : p[x] = lead(p[x]);  }
    int join(int x,int y)   {
        x = lead(x);
        y = lead(y);

        if (x == y) return  0;
        if (s[x] < s[y])    swap(x,y);

        p[y] = x;
        s[x] += s[y];

        return  1;
    }
};
void make_Graph_Eulerian()  {
    DSU::init(vertices);

    for(auto it : index)    {
        int u = it.first.first;
        int v = it.first.second;

        DSU::join(u,v);
    }

}