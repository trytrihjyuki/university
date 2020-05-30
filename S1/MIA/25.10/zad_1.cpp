#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const bool debug = 0;
#define deb if(debug)
#define pb push_back
#define sz size()
#define mp make_pair
const ll maxn = 1005;
const ll k = 25;
int n,a,b;
vector <int> g[maxn];
bool visited[maxn];
int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin>>n;
    for(int i=2; i<=n; i++){
        cin>>a;
        g[a].pb(i);
        g[i].pb(a);
    }
    queue <int> kolejka;
    kolejka.push(1);
    while(!kolejka.empty()){
        int vb = kolejka.front();
        kolejka.pop();
        bool leaf = 1;
        int leaf_sons = 0;
        visited[vb] = 1;
        for(auto u:g[vb]){
            if(!visited[u]){
                leaf = 0;
                if(g[u].sz == 1) leaf_sons++;
                kolejka.push(u);
            }
        }
        if(!leaf && leaf_sons < 3){
            cout<<"No";
            return 0;
        }
    }
    cout<<"Yes";
    return 0;
}