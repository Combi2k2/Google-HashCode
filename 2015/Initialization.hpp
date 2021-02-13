#include <bits/stdc++.h>
#include "ReadInput.hpp"

using namespace std;

typedef pair<Poi,int>   Poi_in_space;

vector<Poi_in_space>    reach[405];
vector<Poi> Centre_vec[405];

void prepare_for_everything()   {
    reach[0].pb(Poi_in_space(Start_Coordinate,0));

    for(int i = 0 ; i < Number_of_Turns ; ++i)  {
        for(Poi_in_space P : reach[i])  {
            int x = P.first.first;
            int y = P.first.second;
            int h = P.second;

            for(int dh = -1 ; dh <= 1 ; ++dh)   {
                int nh = h + dh;

                if (nh < 1)         continue;
                if (nh > Altitude)  continue;

                int nx =  x + get_Wind_dir(nh,x,y).first;
                int ny = (y + get_Wind_dir(nh,x,y).second) % Col;

                if (nx < 0)     continue;
                if (nx >= Row)  continue;

                reach[i + 1].pb(Poi_in_space(Poi(nx,ny),nh));
                Centre_vec[i + 1].pb(Poi(nx,ny));
            }
        }
        sort(reach[i + 1].begin(),reach[i + 1].end());
        reach[i + 1].erase(unique(reach[i + 1].begin(),reach[i + 1].end()),reach[i + 1].end());
        
        sort(Centre_vec[i + 1].begin(),Centre_vec[i + 1].end());
        Centre_vec[i + 1].erase(unique(Centre_vec[i + 1].begin(),Centre_vec[i + 1].end()),Centre_vec[i + 1].end());
    }
}