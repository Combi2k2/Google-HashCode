#include <bits/stdc++.h>

using namespace std;

#define ll  long long
#define ld  double

#define sz(x)   (int)x.size()
#define all(x)  x.begin(),x.end()

#define pb  emplace_back
#define X   first
#define Y   second

typedef pair<int,int>   ii;

vector<ii>  seg[1005];
vector<ii>  servers;

int row;
int pools;

void readInput()    {
    int col;
    cin >> row;
    cin >> col;

    int unavailable_slots;
    cin >> unavailable_slots;
    cin >> pools;

    int number_of_servers;
    cin >> number_of_servers;
    servers.resize(number_of_servers);

    for(int i = 0 ; i < unavailable_slots ; ++i)    {
        int x;  cin >> x;
        int y;  cin >> y;
        
        seg[x].pb(y,0);
    }
    for(int i = 0 ; i < number_of_servers ; ++i)    {
        int Siz;    cin >> Siz;
        int Cap;    cin >> Cap;
        
        servers[i] = ii(Siz,Cap * number_of_servers + i);
    }
    for(int i = 0 ; i < row ; ++i)  {
        sort(all(seg[i]));
        vector<ii>  vec;
        vec.swap(seg[i]);

        sort(all(vec));

        int L = 0;

        for(ii  P : vec)    {
            int v = P.first;
            if (v > L)
                seg[i].pb(L,v - 1);
            
            L = v + 1;
        }
        if (L < col)    seg[i].pb(L,col - 1);
    }
    sort(all(servers),[&](ii  sv1,ii  sv2)  {
        int cap1 = sv1.second / number_of_servers;
        int cap2 = sv2.second / number_of_servers;

        if (cap1 != cap2)   return  cap1 > cap2;
        else                return  sv1.first > sv2.first;
    });
}