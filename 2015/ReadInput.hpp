#include <bits/stdc++.h>

using namespace std;

#define ll  long long
#define ld  double

#define sz(x)   (int)x.size()
#define all(x)  x.begin(),x.end()

#define pb  emplace_back
#define X   first
#define Y   second

typedef pair<int,int>   Poi;

int Row;
int Col;
int Attitude;

vector<Poi> Imp_Cells;
vector<Poi> Wind_dir[8];

Poi Start_Coordinate;

int Coverage_Radius;
int Number_of_Turns;
int Number_of_Balloons;

void readInput()    {
    cin >> Row;
    cin >> Col;
    cin >> Attitude;

    int L;  cin >> L;
    cin >> Coverage_Radius;
    cin >> Number_of_Balloons;
    cin >> Number_of_Turns;

    cin >> Start_Coordinate.X;
    cin >> Start_Coordinate.Y;

    for(int i = 0 ; i < L ; ++i)    {
        int x;  cin >> x;
        int y;  cin >> y;

        Imp_Cells.pb(x,y);
    }
    for(int i = 1 ; i <= Attitude ; ++i)
        for(int j = 0 ; j < Row ; ++j)
        for(int k = 0 ; k < Col ; ++k)  {
            int a;  cin >> a;
            int b;  cin >> b;

            Wind_dir[i].pb(a,b);
        }
}
Poi get_Wind_dir(int h,int x,int y) {   return  Wind_dir[h][x * Col + y];   }