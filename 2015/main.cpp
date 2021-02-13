#include <bits/stdc++.h>
#include "Initialization.hpp"

using namespace std;

const int   R = 80;
const int   C = 305;

int dp[9][R][C][405];
int Sum[R][C][405];

int  Count[R][C];

Poi_in_space from[9][R][C][405];

bool not_covered(int x,int y,int T) {
    if (y)  return  Sum[x][y][T] - Sum[x][y - 1][T];
    else    return  Sum[x][y][T];
}

int main()  {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    freopen("hashcode_2015_final_round.in","r",stdin);
    freopen("my_output.out","w",stdout);

    readInput();    return  0;
    prepare_for_everything();

    for(int T = 1 ; T <= Number_of_Turns ; ++T) {
        for(Poi P : Imp_Cells)  Sum[P.first][P.second][T] = 1;

        for(int i = 0 ; i < Row ; ++i)
        for(int j = 1 ; j < Col ; ++j)
            Sum[i][j][T] += Sum[i][j - 1][T];
    }
    vector<vector<int> > routes(Number_of_Balloons);

    return  0;

    while (Number_of_Balloons--)    {
        cerr << 100.0 - 100.0 * Number_of_Balloons / sz(routes) << "%\n";

        Poi_in_space Optimal_point;
        int          Optimal_time;
        int best_val = -1;

        //get optimal route for current balloons using dp

        for(int T = 1 ; T <= Number_of_Turns ; ++T)    {
            for(Poi Cen : Centre_vec[T])    {
                int x = Cen.first;
                int y = Cen.second;

                int&res = Count[x][y];  res = 0;

                for(int i = 0 ; i < Row ; ++i)  if (abs(x - i) <= Coverage_Radius)  {
                    int delta = sqrt(Coverage_Radius * Coverage_Radius - (x - i) * (x - i));

                    int l = y - delta;
                    int r = y + delta;

                    if (delta + delta >= Col)   res += Sum[i][Col - 1][T];
                    else    {
                        if (l < 0)      l += Col;
                        if (r >= Col)   r -= Col;

                        if (l <= r) res += Sum[i][r][T] - Sum[i][l - 1][T];
                        else        res -= Sum[i][l][T] - Sum[i][r - 1][T] - Sum[i][Col - 1][T];
                    }
                }
            }
            for(Poi_in_space P : reach[T])      dp[P.second][P.first.first][P.first.second][T] = -1e9;
            for(Poi_in_space P : reach[T - 1])  {
                int x = P.first.first;
                int y = P.first.second;
                int h = P.second;

                for(int dh = -1 ; dh <= 1 ; ++dh)   {
                    int nh = h + dh;

                    if (nh < 1)         continue;
                    if (nh > Altitude)  continue;

                    int nx =  x + get_Wind_dir(nh,x,y).first;
                    int ny = (y + get_Wind_dir(nh,x,y).second) % Col;

                    if (nx <  0)    continue;
                    if (nx >= Row)  continue;

                    if (dp[nh][nx][ny][T] < dp[h][x][y][T - 1] + Count[nx][ny]) {
                        dp[nh][nx][ny][T] = dp[h][x][y][T - 1] + Count[nx][ny];
                        from[nh][nx][ny][T] = P;
                    }
                }
            }
            for(Poi_in_space P : reach[T])
                if (best_val < dp[P.second][P.first.first][P.first.second][T])  {
                    best_val = dp[P.second][P.first.first][P.first.second][T];
                    Optimal_point = P;
                    Optimal_time  = T;
                }
        }
        //trace the route and update some important cells

        if (best_val <= 0)  break;

        vector<int> &current_route = routes[sz(routes) - Number_of_Balloons - 1];

        int x = Optimal_point.first.first;
        int y = Optimal_point.first.second;
        int h = Optimal_point.second;

        for(int i = Optimal_time ; i > 0 ; --i) {
            Poi_in_space prev_dest = from[h][x][y][i];

            current_route.pb(h - prev_dest.second);

            x = prev_dest.first.first;
            y = prev_dest.first.second;
            h = prev_dest.second;
        }
        reverse(all(current_route));

        assert(x == Start_Coordinate.first);
        assert(y == Start_Coordinate.second);
        assert(h == 0);

        x = Optimal_point.first.first;
        y = Optimal_point.first.second;
        h = Optimal_point.second;

        while (0 <= x && x < Row && sz(current_route) < Number_of_Turns)    {
            int nx = x + get_Wind_dir(h,x,y).first;
            int ny = y + get_Wind_dir(h,x,y).second;

            current_route.pb(0);

            x = nx;
            y = ny;
        }
        //update the covered resident cell in different turns
        x = Start_Coordinate.X;
        y = Start_Coordinate.Y;
        h = 0;
        
        for(int T = 0 ; T < sz(current_route) ; ++T)    {
            h += current_route[T];
            int nx = x + get_Wind_dir(h,x,y).first;
            int ny = y + get_Wind_dir(h,x,y).second;

            for(Poi Cell : Imp_Cells)   if (not_covered(Cell.X,Cell.Y,T))   {
                int dx = abs(nx - Cell.X);
                int dy = min(abs(ny - Cell.Y),Col - abs(ny - Cell.Y));

                if (dx * dx + dy * dy <= Coverage_Radius * Coverage_Radius)
                    for(int i = Cell.Y ; i < Col ; ++i)
                        Sum[Cell.X][i][T]--;
            }
        }
    }
    for(vector<int> &vec : routes)  {
        if (vec.empty())
            vec.resize(Number_of_Turns);
        
        for(int dh : vec)
            cout << dh << " ";
        
        cout << "\n";
    }
}