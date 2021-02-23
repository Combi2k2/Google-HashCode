#include <bits/stdc++.h>

using namespace std;

#define ll  long long
#define ld  double

#define sz(x)   (int)x.size()
#define all(x)  x.begin(),x.end()

#define pb  emplace_back
#define X   first
#define Y   second

string INPUT_FILE;

int number_of_photos;
int type[100005];

vector<string> tag_in_string[100005];

bitset<500> tag1[100005];
vector<int> tag2[100005];

map<string,int> label;
char subTask;

void readInput()    {
    cin >> number_of_photos;

    for(int i = 0 ; i < number_of_photos ; ++i) {
        char T; cin >> T;
        type[i] = (T == 'H');

        int number_of_tags;
        cin >> number_of_tags;

        while (number_of_tags--)    {
            string tag;
            cin >> tag;

            tag_in_string[i].pb(tag);
            label[tag] = 0;
        }
    }
    int tot = 0;

    for(auto &it : label)
        it.second = tot++;
    
    for(int i = 0 ; i < number_of_photos ; ++i) {
        for(string S : tag_in_string[i])    {
            tag2[i].pb(label[S]);

            if (subTask != 'b' && subTask != 'c')
                tag1[i][label[S]] = 1;
        }
        
        sort(all(tag2[i]));
    }
}
bitset<500> current_tags1;
vector<int> current_tags2;

int get_point(int x)    {
    int size1 = 0;
    int size2 = 0;
    int size3 = 0;

    if (subTask == 'b' || subTask == 'c')   {
        int pointer1 = 0;
        int pointer2 = 0;

        while (pointer1 < sz(current_tags2) && pointer2 < sz(tag2[x])) {
            int a = current_tags2[pointer1];
            int b = tag2[x][pointer2];

            if (a < b)  {   size1++;    pointer1++; continue;   }
            if (b < a)  {   size2++;    pointer2++; continue;   }
            
            pointer1++;
            pointer2++;
            size3++;
        }
        size1 += sz(current_tags2) - pointer1;
        size2 += sz(tag2[x]) - pointer2;
    }
    else    {
        bitset<500> temp = current_tags1 & tag1[x];

        size1 = (current_tags1 ^ temp).count();
        size2 = (tag1[x] ^ temp).count();
        size3 = temp.count();
    }
    return  min(min(size1,size2),size3);
}
vector<int> answer;
int beWith[100005];

int main(int argc,char **argv)  {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    INPUT_FILE = argv[1];
    subTask = INPUT_FILE[0];

    freopen((INPUT_FILE + ".txt").c_str(),"r",stdin);
    freopen((INPUT_FILE + ".out").c_str(),"w",stdout);

    readInput();
    
    set<int> remaining_photos;

    int last_vertical_pic = -1;
    bool found = false;

    for(int i = 0 ; i < number_of_photos ; ++i) {
        if (type[i] && !found)  {
            current_tags2 = tag2[i];
            current_tags1 = tag1[i];

            answer.pb(i);
            found = true;
            continue;
        }
        else if (!type[i])  {
            if (last_vertical_pic < 0)  {
                last_vertical_pic = i;
                continue;
            }
            else    {
                beWith[i] = last_vertical_pic;
                beWith[last_vertical_pic] = i;

                for(int x : tag2[last_vertical_pic])
                    tag2[i].pb(x);
                
                sort(all(tag2[i]));
                tag2[i].erase(unique(all(tag2[i])),tag2[i].end());

                tag1[i] |= tag1[last_vertical_pic];
                last_vertical_pic = -1;
            }
        }
        remaining_photos.insert(i);
    }
    
    while (sz(remaining_photos))    {
        int best_score = -1;
        int best_next_pic = -1;

        for(int x : remaining_photos)   {
            int point = get_point(x);

            if (best_score < point) {
                best_score = point;
                best_next_pic = x;
            }
        }
        assert(best_next_pic >= 0);
        answer.pb(best_next_pic);
        
        current_tags1 = tag1[best_next_pic];
        current_tags2 = tag2[best_next_pic];

        remaining_photos.erase(best_next_pic);
    }
    cout << sz(answer) << "\n";

    for(int x : answer) {
        if (type[x])    cout << x << "\n";
        else            cout << x << " " << beWith[x] << "\n";
    }
}
