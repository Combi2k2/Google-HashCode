#include<bits/stdc++.h>
using namespace std;
 
#define fi first
#define se second
#define FOR(a, b, c) for(int a = b; a <= c; ++a)
#define FORW(a,b,c) for(int a = b; a >= c; --a)
#define pb push_back
// #define int long long
#define SZ(a) (int)(a.size())
 
const int MOD = 998244353;
const int oo = 2e9;
const int N = 1e3 + 100;
typedef pair<int, int> ii;
typedef pair<ii, int> iii;

struct slots {
    int lef, rig;
    slots(int lef = 0, int rig = 0): lef(lef), rig(rig) {}
    bool operator < (const slots &x) const {return rig - lef + 1 > x.rig - x.lef + 1;}
};

struct position {
    int row, lef, pool;
    position(int row = 0, int lef = 0, int pool = 0) : row(row), lef(lef), pool(pool) {}
};

int row, col, unavail, pcnt, scnt;
int pcap[N][N], rem_slot[N]; // capacity of a pool on a row : pool - row
ii sver[N * N];
bool slot[N][N];
vector<slots> aslot[N];
vector<int> sv;
vector<ii> tmp;
vector<position> trace[N];


bool cmp(const int x, const int y) { 
    if(sver[x].se * sver[y].fi != sver[x].fi * sver[y].se)
        return sver[x].se * sver[y].fi > sver[x].fi * sver[y].se;
    return sver[x].fi > sver[y].fi;
}
bool cmp1(const ii x, const ii y) {
    if(x.fi != y.fi) return x.fi < y.fi;
    return rem_slot[x.se] > rem_slot[y.se];
}
bool cmp2(const ii x, const ii y) {
    return x.se - x.fi > y.se - y.fi;
}


bool check(int sid, int rid, int pid) {
    int maxn = -1;
    if(SZ(aslot[rid]) == 0) return false;
    FOR(i, 0, SZ(aslot[rid]) - 1) if(maxn == -1 || aslot[rid][i].rig - aslot[rid][i].lef > aslot[rid][maxn].rig - aslot[rid][maxn].lef)
        maxn = i;
    if(aslot[rid][maxn].rig - aslot[rid][maxn].lef + 1 < sver[sid].fi)
        return false;
    pcap[pid][rid] += sver[sid].se;
    trace[sid] = {{rid, aslot[rid][maxn].lef}, pid};
    aslot[rid][maxn].lef += sver[sid].fi;
    // rem_slot[rid] -= sver[sid].fi;
    return true;
}

void prepare() {
    FOR(i, 1, pcnt) FOR(j, 1, row) pcap[i][j] = 0;
    FOR(i, 1, row) {
        rem_slot[i] = col;
        FOR(j, 1, col) if(slot[i][j] == false) rem_slot[i] -= 1;

        aslot[i].clear();
        int st = 0; while(st < col && slot[i][st + 1] == 0) st += 1;
        while(st < col) {
            int rig = st + 1;
            while(rig < col && slot[i][rig + 1] == 1) rig += 1;
            aslot[i].pb({st + 1, rig});
            st = rig + 1;
            while(st < col && slot[i][st + 1] == 0) st += 1;
        }
    }
}

int solve() {
    sort(sv.begin(), sv.end(), cmp); 
    tmp.clear();
    prepare();

    priority_queue<ii, vector<ii>, greater<ii> > pq;
    FOR(i, 1, pcnt) pq.push({0, i});

    for(auto x: sv) {
        auto minn = pq.top().se; pq.pop();
        tmp.clear();
        FOR(i, 1, row) tmp.pb({pcap[minn][i], i});
        sort(tmp.begin(), tmp.end(), cmp1);

        for(auto v: tmp) if(check(x, v.se, minn)) break;
            
        int sum = 0, maxn = 0;
        FOR(i, 1, row) sum += pcap[minn][i], maxn = max(maxn, pcap[minn][i]);
        pq.push({sum - maxn, minn});
    }
    
    int res = oo;
    FOR(i, 1, pcnt) {
        int cur = 0, sum = 0;
        FOR(j, 1, row) sum += pcap[i][j], cur = max(cur, pcap[i][j]);
        res = min(res, sum - cur);
    }
    return res;
}

signed main()
{
    srand(time(NULL));
    freopen("dc.in", "r", stdin);
    scanf("%d%d%d%d%d", &row, &col, &unavail, &pcnt, &scnt);

    memset(slot, 1, sizeof slot);
    FOR(i, 1, row) rem_slot[i] = col;
    FOR(i, 1, unavail) {
        int x, y; scanf("%d%d", &x, &y);
        rem_slot[x] -= 1;
        slot[x][y] = false;
    }
    FOR(i, 1, scnt) {
        sv.pb(i);
        scanf("%d%d", &sver[i].fi, &sver[i].se); // size - capacity
    }
    prepare();

    int res = 0;
    FOR(i, 1, 1) res = max(res, solve());
    cout << res;
}
